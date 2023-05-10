pipeline {
    agent any
    
    tools {
        jdk 'jdk11'
        maven 'maven3'
    }
    
    environment{
        SCANNER_HOME= tool 'sonar-scanner'
    }

    stages {
         stage('Cleanup Workspace'){
            steps {
                script {
                    cleanWs()
                }
            }
        }


        stage('Git Checkout ') {
            steps {
                git credentialsId: 'github', branch: 'main', changelog: false, poll: false, url: 'https://github.com/GhazouaniHichem/MERN-app-CI-CD-pipeline.git'
            }
        }
        
        stage('Code Build') {
            steps {
                dir('client') {
                    sh "npm install"
                }
                dir('server') {
                    sh "npm install"
                }
            }
        }
        
/*         stage('Run Test Cases') {
            steps {
                dir('client') {
                    sh "npm run test"
                }
                dir('server') {
                    sh "npm run test"
                }
            }
        }
*/        
        stage('Sonarqube Analysis') {
            steps {
                dir('client') {
                    withSonarQubeEnv('sonar-server') {
                        sh ''' $SCANNER_HOME/bin/sonar-scanner -Dsonar.projectName=NodeJS-App \
                        -Dsonar.sources=. \
                        -Dsonar.css.node=. \
                        -Dsonar.projectKey=NodeJS-App '''
                    }
                }
                dir('server') {
                    withSonarQubeEnv('sonar-server') {
                        sh ''' $SCANNER_HOME/bin/sonar-scanner -Dsonar.projectName=NodeJS-App \
                        -Dsonar.sources=. \
                        -Dsonar.css.node=. \
                        -Dsonar.projectKey=NodeJS-App '''
                    }
                }
            }
        }
        
/*         stage('OWASP Dependency Check') {
            steps {
                dir('server') {
                   dependencyCheck additionalArguments: '--scan ./   ', odcInstallation: 'DP'
                   dependencyCheckPublisher pattern: '**//*dependency-check-report.xml'
                }
            }
        }
*/        
        stage('Docker Build & Push') {
            steps {
                   script {
                       withDockerRegistry([ credentialsId: 'docker-cred', url: '' ]) {
                            dir('client') {
                                sh "docker build -t movies-mern-app-frontend ."
                                sh "docker tag webapp ghazouanihm/movies-mern-app-frontend:${BUILD_NUMBER}"
                                sh "docker push ghazouanihm/movies-mern-app-frontend:${BUILD_NUMBER}"
                            }
                            dir('server') {
                                sh "docker build -t movies-mern-app-backend ."
                                sh "docker tag webapp ghazouanihm/movies-mern-app-backend:${BUILD_NUMBER}"
                                sh "docker push ghazouanihm/movies-mern-app-backend:${BUILD_NUMBER}"
                            }
                        }
                   } 
            }
        }
        
        stage('Docker Image scan') {
            steps {
                    sh "trivy image ghazouanihm/movies-mern-app-frontend:${BUILD_NUMBER}"
                    sh "trivy image ghazouanihm/movies-mern-app-backend:${BUILD_NUMBER}"
            }
        }

        stage('Update Deployment File') {
            environment {
                GIT_REPO_NAME = "MERN-app-CI-CD-gitops"
                GIT_USER_NAME = "GhazouaniHichem"
            }
            steps {
                withCredentials([string(credentialsId: 'github-cred', variable: 'GITHUB_TOKEN')]) {
                    sh '''
                        git config user.email "ghazouanih68@gmail.com"
                        git config user.name "Ghazouani Hichem"
                        BUILD_NUMBER=${BUILD_NUMBER}
                        sed -i "s/replaceImageTag/${BUILD_NUMBER}/g" kubernetes/frontend-deployment.yaml
                        sed -i "s/replaceImageTag/${BUILD_NUMBER}/g" kubernetes/server-deployment.yaml
                        git add .
                        git commit -m "Update deployment image to version ${BUILD_NUMBER}"
                        git push https://${GITHUB_TOKEN}@github.com/${GIT_USER_NAME}/${GIT_REPO_NAME} HEAD:main
                    '''
                }
            }
        }        
    }
}
