#!/bin/bash
while true; do
echo "------- File Management Program -------"
echo "1. Add file"
echo "2. Edit file"
echo "3. Delete file"
echo "4. Rename file"
echo "5. Copy file"
echo "6. List files"
echo "7. show file"
echo "8. Exit"
read -p "Enter your choice (1-8): " choice

case $choice in
    1)
        read -p "Enter file name: " filename
        touch $filename
        echo "File created successfully"
        ;;
    2)
        read -p "Enter file name: " filename
        nano $filename
        ;;
    3)
        read -p "Enter file name: " filename
        rm $filename
        echo "File deleted successfully"
        ;;
    4)
        read -p "Enter current file name: " currentname
        read -p "Enter new file name: " newname
        mv $currentname $newname
        echo "File renamed successfully"
        ;;
    5)
        read -p "Enter source file name: " sourcefile
        read -p "Enter destination file name: " destinationfile
        cp $sourcefile $destinationfile
        echo "File copied successfully"
        ;;
    6)  echo "Danh sach file:"
        ls -l
        ;;
    7)  read -p "Enter file name: " filename
        cat $filename
        ;;
    8)  
        echo "Exiting program."
        exit 0
        ;;    
    *)
        echo "Invalid choice"
        ;;
esac
done
