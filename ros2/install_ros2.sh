#!/bin/bash
echo "正在为 Ubuntu 24.04 (noble) 安装 ROS 2 Jazzy..."

# 更新系统
sudo apt update && sudo apt upgrade -y

# 安装基础工具
sudo apt install curl software-properties-common locales -y
sudo locale-gen en_US en_US.UTF-8
sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8

# 添加ROS源
sudo add-apt-repository universe
sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu noble main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null

# 安装ROS
sudo apt update
sudo apt install ros-jazzy-desktop -y

# 环境设置
echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc
source ~/.bashrc

# 安装开发工具
sudo apt install python3-colcon-common-extensions python3-rosdep2 -y
sudo rosdep init || true
rosdep update || true

echo "安装完成！重启终端或运行：source ~/.bashrc"
echo "测试命令：ros2 run turtlesim turtlesim_node"
