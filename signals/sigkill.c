#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/wait.h>



int main(int argc, char* argv[]){
    int pid = fork();
    if(pid == -1){return 1;}
    else if(pid == 0){
        while(1){
            printf("come high level code\n");
            usleep(50000);
        }
    }
    else{
        int num;
        sleep(1);
        kill(pid, SIGKILL);
        wait(&num);
        printf("child return %d\n", num);
    }

    return 0;
}