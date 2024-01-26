#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h> 
#include <dirent.h>
#include <sys/stat.h>

//kiem tra file
bool file_exists (char *filename) {
 struct stat buffer; 
 return (stat (filename, &buffer) == 0);
}
//Doc file
void read_file(char* file) {
int fd;
char buff[10000];
fd = open(file, O_RDONLY);
if (fd == -1) {
printf("error file not found\n");
}
while (read(fd, buff, sizeof(buff)) != 0) {
printf("%s", buff);
}
printf("\n");
}

//xoa file

void delete(char* file) {
int st = remove(file);
if (st == 0 ) {
printf("xoa file thanh cong\n");
} else {
printf ("xoa file that bai \n");
}
}

//tao file

void create(char* file) {
int fd;
fd = open(file, O_CREAT, 0666);
if (fd == -1) {
printf("tao file that bai\n");
} else {

printf("tao file thanh cong\n");
}
}


//kiem tra quyen cua file

void permissions(char* file){
 struct stat st;
 char modeval[9];
 if(stat(file, &st) == 0){
 mode_t perm = st.st_mode;
 printf("%c",modeval[0] = (perm & S_IRUSR) ? 'r' : '-');
 printf("%c",modeval[1] = (perm & S_IWUSR) ? 'w' : '-');
 printf("%c",modeval[2] = (perm & S_IXUSR) ? 'x' : '-');
 printf("%c",modeval[3] = (perm & S_IRGRP) ? 'r' : '-');
 printf("%c",modeval[4] = (perm & S_IWGRP) ? 'w' : '-');
 printf("%c",modeval[5] = (perm & S_IXGRP) ? 'x' : '-');
 printf("%c",modeval[6] = (perm & S_IROTH) ? 'r' : '-');
 printf("%c",modeval[7] = (perm & S_IWOTH) ? 'w' : '-');
 printf("%c\n",modeval[8] = (perm & S_IXOTH) ? 'x' : '-'); 
 }
 else{
 printf("%s\n", strerror(errno));
 } 
}

//ham main
int main(int argc, char *argv[]) {
    if (argc < 3) {
        puts("Usage: program_name command filename");
        return 1;
    }

   // check(argc);

    if (strcmp(argv[1], "crea") == 0) {
        create(argv[2]);
        exit(0);
    } else {
        if (file_exists(argv[2]) == true) {
            if (strcmp(argv[1], "per") == 0) {
                permissions(argv[2]);
                exit(0);
            }
            if (strcmp(argv[1], "del") == 0) {
                remove(argv[2]);
                exit(0);
            }
            if (strcmp(argv[1], "rd") == 0) {
                read_file(argv[2]);
                exit(0);
            }
        }
        if (file_exists(argv[2]) == false) {
            puts("File không tồn tại hoặc tham số truyền vào sai.");
        }
    }

    return 0;
}





