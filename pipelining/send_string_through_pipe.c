#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>


int main(){
    int fd[2];
    if(pipe(fd) == -1){return 2;}

    int pid = fork();
    if(pid == -1){return 1;}

    if(pid == 0){
        close(fd[0]);
        char str[200];
        printf("Input String: ");
        fgets(str, 200, stdin);

        int n = strlen(str) + 1;
        printf("n = %d\n", n);

        str[strlen(str) - 1] = '\0'; // indicate end of string

        n = strlen(str) + 1;
        printf("n = %d\n", n);
        if(write(fd[1], &n, sizeof(int)) < 0){return 3;}
        if(write(fd[1], str, strlen(str) + 1) < 0){return 3;}
        close(fd[1]);
    }
    else{
        close(fd[1]);
        int n;
        char str[200];

        if(read(fd[0], &n, sizeof(int)) < 0){return 3;}
        if(read(fd[0], str, sizeof(char) * n) < 0){return 3;}
        close(fd[0]);

        printf("Get String = %s\n", str);
    }
    return 0;
}

