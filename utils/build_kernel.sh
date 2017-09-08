#!/bin/bash
#@Author: Rishi Soni
#@brief: Automates building a kernel from source
#@date: 9 September 2017
#@version: 1.0

echo "Script to build kernel from source"
echo "Running now ..."
echo "Installing required tools ..."
sudo apt-get install libncurses5-dev gcc make git exuberant-ctags bc libssl-dev
sudo apt-get update
echo "Removing any existing kernel archive file"
sudo rm -rf linux-*
echo "Downloading kernel version 4.12.10 from source"
sudo wget https://cdn.kernel.org/pub/linux/kernel/v4.x/linux-4.12.10.tar.xz
read -p "Press [Enter] to continue..."
echo "Unpacking kernel file ...."
tar -xvJf linux-4.12.10.tar.xz
cd linux-4.12.10
echo "Using default configuration for kernel build"
sudo make defconfig
echo "Compiling kernel ...."
sudo make
echo "Installing modules"
sudo make modules_install
sudo make install
echo "Updating files such that new kernel boots up at reboot"
update-initramfs -c -k 4.12.10
sudo update-grub
sudo update-grub2
echo "Please reboot your system use new kernel!"