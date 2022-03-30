#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    if(mkfifo("myfifo1", 0777) == -1){
        if(errno != EEXIST){
            return 1;
        }
    }
    int pid = fork();
    if(pid < 0){return 3;}
    else if(pid > 0){
        int fd = open("myfifo1", O_WRONLY);
        char* x = "string";
        if(write(fd, &x, sizeof(char)*10) == -1){
            return 2;
        }
    }
    else{
        int fd = open("myfifo1", O_RDONLY);
        char* y[10];
        if(read(fd, &y, sizeof(char)*10) == -1){
            return 2;
        }
        printf("Get from parent: %s\n", *y); 
    }
    return 0;
}
