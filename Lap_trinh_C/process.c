#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <libgen.h>
#include <linux/limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

#define PROC_DIR "/proc/"
#define EXE_LINK "/exe"

bool getlinkedpath(const char* exelinkpath, char* path) {
    ssize_t len = readlink(exelinkpath, path, PATH_MAX);
    if (len == -1) {
        printf("readlink() failed with error %d\n", errno);
        return false;
    }
    path[len] = '\0';
    return true;
}

void list_processes() {
    DIR *dir = opendir(PROC_DIR);
    if (dir == NULL) {
        printf("opendir() failed with error %d\n", errno);
        return;
    }
    struct dirent *de;
    while ((de = readdir(dir))) {
        const char *pid = de->d_name;
        if (!isdigit(*pid)) {
            continue;
        }

        char exelinkpath[PATH_MAX];
        snprintf(exelinkpath, sizeof(exelinkpath), "%s%s%s", PROC_DIR, pid, EXE_LINK);
        struct stat st;
        if (stat(exelinkpath, &st) == -1) {
            continue;
        }

        char path[PATH_MAX];
        if (!getlinkedpath(exelinkpath, path)) {
            printf("getlinkedpath() failed for PID %s, skipping entry...\n", pid);
            continue;
        }
        printf("[%s] %s\n", pid, basename(path));
    }
    closedir(dir);
}

void stop_process(int pid) {
    if (kill(pid, SIGSTOP) == 0) {
        printf("Process with ID %d stopped successfully\n", pid);
    } else {
        printf("Failed to stop process with ID %d, review process ID\n", pid);
    }
}

int main() {
    int key, pid;
    while (1) {
        puts("PROCESS MANAGEMENT\n");
        puts("1. Show the processes running on the system\n");
        puts("2. Stop a process\n");
        puts("3. Exit\n");
        puts("Enter selection\n");
        scanf("%d", &key);
        getchar(); // consume the newline character left in the buffer
        switch (key) {
            case 1:
                list_processes();
                break;
            case 2:
                puts("Enter the ID of the process\n");
                scanf("%d", &pid);
                getchar(); // consume the newline character left in the buffer
                stop_process(pid);
                break;
            case 3:
                exit(0);
                break;
            default:
                puts("Invalid selection, please try again\n");
                break;
        }
    }
    return 0;
}
