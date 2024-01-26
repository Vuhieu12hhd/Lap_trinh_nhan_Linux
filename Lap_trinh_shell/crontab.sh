#!/bin/bash
while true; do
echo "1. Set up a new schedule"
echo "2. Display current schedule"
echo "3. Remove a schedule"
echo "4. Quit"

read -p "Enter your choice: " choice

case $choice in
    1)
        read -p "Enter the schedule (in crontab format): " schedule
        (crontab -l; echo "$schedule") | crontab -
        ;;
    2)  echo "task list:"
        crontab -l
        ;;
    3)
        read -p "Enter the schedule to remove (in crontab format): " schedule
        (crontab -l | grep -v "$schedule") | crontab -
        ;;
    4)
        echo "Exiting..."
        exit 0
        ;;
    *)
        echo "Invalid choice"
        exit 1
        ;;
esac
done
#* * * * * echo "hello" >> /home/vuhieu/Desktop/hello.txt
