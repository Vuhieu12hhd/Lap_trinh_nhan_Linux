#!/bin/bash

# Thiết lập thời gian hệ thống thành 9 giờ 30 phút ngày 7 tháng 3 năm 2023
sudo timedatectl set-ntp false
sudo date -s "2023-03-08 09:30:00"
#sudo timedatectl set-ntp true



