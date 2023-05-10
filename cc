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




sh "curl -v -k --user admin:****** -X POST -H 'cache-control: no-cache' -H 'content-type: application/x-www-form-urlencoded' --data 'IMAGE_TAG=${IMAGE_TAG}' 'http://35.180.57.111:8080/job/******/buildwithParameter?token=******'"