#!/bin/bash

<<Kiem tra xem gói phần mềm đã được cài đặt hay chưa
if dpkg -s vlc &> /dev/null; then
    echo "Gói phần mềm đã được cài đặt."
else
    # Cài đặt gói phần mềm nếu chưa được cài đặt
    sudo apt-get -y install vlc
    echo "Đã cài đặt gói phần mềm."
fi
Kiem
# Gỡ bỏ gói phần mềm
sudo apt-get -y remove vlc
echo "Đã gỡ bỏ gói phần mềm."

