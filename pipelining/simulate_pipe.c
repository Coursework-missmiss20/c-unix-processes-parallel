#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// simulate ping -c 5 google.com | grep time
int main(){
    int fd[2];
    if(pipe(fd) == -1){return 2;}

    int pid = fork();
    if(pid == -1){return 1;}

    if(pid == 0){
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("ping", "ping", "-c", "5", "google.com", NULL); // now child program get replaced by the ping program
    }

    int pid2 = fork();
    if(pid2 < 0){return 1;}
    if(pid2 == 0){
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("grep", "grep", "time", NULL);
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(pid, NULL, 0);
    waitpid(pid2, NULL, 0);


    return 0;
}

