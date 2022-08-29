#!/bin/bash

apt-get update

apt-get install vim -y

<<<<<<< Updated upstream
apt-get install zsh -y

chsh -s /bin/zsh

apt-get install wget -y

wget --no-check-certificate https://github.com/robbyrussell/oh-my-zsh/raw/master/tools/install.sh -O - | sh

bash

zsh




#!/bin/bash

apt-get update

apt-get install vim -y

=======
>>>>>>> Stashed changes

# init zsh and oh my zsh

apt-get install zsh -y
apt-get install git -y
chsh -s /bin/zsh
apt-get install wget -y
<<<<<<< Updated upstream
wget --no-check-certificate https://github.com/robbyrussell/oh-my-zsh/raw/master/tools/install.sh -O - | sh
=======
# wget --no-check-certificate https://github.com/robbyrussell/oh-my-zsh/raw/master/tools/install.sh -O - | sh
>>>>>>> Stashed changes
zsh

# 🖼️ install the GUI program
# more infomation come from here : 📚 https://gist.github.com/sorny/969fe55d85c9b0035b0109a31cbcb088

apt-get install xserver-xorg x11-xserver-utils -y


# 💻 host should exec this command
# xhost +

# 😕 this step still can setting when docker start like this
# eg: docker run -e DISPLAY=$ip:0 sshipway/xclock
# ‼️  this ip is the host ip , isn`t the docker container ip

ip=$(ifconfig en0 | grep inet | awk '$1=="inet" {print $2}')
export DISPLAY=$ip:0.0





