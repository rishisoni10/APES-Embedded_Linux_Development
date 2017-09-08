#!/bin/bash

cd /home/rishisoni/Desktop/APES/linux-4.12.10/
make defconfig
make modules_install
make install
update-initramfs -c -k 4.12.10
update-grub2

