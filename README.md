# MoonFlix

    Fullstack Responsive Movie Website 2022

# Video tutorial

[Part 1](https://youtu.be/j-Sn1b4OlLA)<br>

[Part 2](https://youtu.be/Q_uLi4f27Lc)<br>


# Preview

!["Fullstack Responsive Movie Website 2022"](https://user-images.githubusercontent.com/67447840/207322539-8fcd83e1-8424-4922-980c-91d20cdf761c.png "Fullstack Responsive Movie Website 2022")

!["Fullstack Responsive Movie Website 2022"](https://user-images.githubusercontent.com/67447840/207322676-cbf56b14-8e23-4622-bbd9-76e6cbe619a8.png "Fullstack Responsive Movie Website 2022")








#############################-----STEPS-----###########################


--- JDK & Maven Installation ---

sudo apt-get update -y
sudo apt install openjdk-11-jre -y
sudo apt-get install maven -y

--- Docker Installation ---

sudo apt-get update
sudo apt-get install ca-certificates curl gnupg

sudo install -m 0755 -d /etc/apt/keyrings
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg
sudo chmod a+r /etc/apt/keyrings/docker.gpg

echo \
  "deb [arch="$(dpkg --print-architecture)" signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/ubuntu \
  "$(. /etc/os-release && echo "$VERSION_CODENAME")" stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
  
  sudo apt-get update
  
  sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
  
service docker restart
sudo usermod -aG docker $USER
newgrp docker
sudo chmod 666 /var/run/docker.sock
sudo systemctl restart docker
======================================================================================================================================

--- INSTALL JENKINS ---

sudo apt install openjdk-11-jre

curl -fsSL https://pkg.jenkins.io/debian-stable/jenkins.io-2023.key | sudo tee \
  /usr/share/keyrings/jenkins-keyring.asc > /dev/null
echo deb [signed-by=/usr/share/keyrings/jenkins-keyring.asc] \
  https://pkg.jenkins.io/debian-stable binary/ | sudo tee \
  /etc/apt/sources.list.d/jenkins.list > /dev/null
sudo apt-get update -y 
sudo apt-get install jenkins -y

sudo systemctl enable jenkins
sudo systemctl start jenkins
sudo systemctl status jenkins



---TRIVY INSTALLATION STEPS---

sudo apt-get install wget apt-transport-https gnupg lsb-release

wget -qO - https://aquasecurity.github.io/trivy-repo/deb/public.key | gpg --dearmor | sudo tee /usr/share/keyrings/trivy.gpg > /dev/null

echo "deb [signed-by=/usr/share/keyrings/trivy.gpg] https://aquasecurity.github.io/trivy-repo/deb $(lsb_release -sc) main" | sudo tee -a /etc/apt/sources.list.d/trivy.list

sudo apt-get update

sudo apt-get install trivy -y



################ Minikube PortForwarding ################"


kubectl port-forward svc/argocd-server -n argocd --address 0.0.0.0 8080:443