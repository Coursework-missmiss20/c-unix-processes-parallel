#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/wait.h>

int correct = 0;

void handle_sigusr1(int sig){
    if(correct == 0) 
    printf("5 seconds has passed\n");
}

int main(int argc, char* argv[]){
    int pid = fork();
    if(pid == -1){return 1;}

    if(pid == 0){
        sleep(5);
        kill(getppid(), SIGUSR1); // nned to handle this SIGUSR1 signal
    }
    else{
        struct sigaction sa = {0};
        sa.sa_handler = &handle_sigusr1;
        sa.sa_flags = SA_RESTART;
        sigaction(SIGUSR1, &sa, NULL);

        int x;
        printf("Result:  ");
        scanf("%d", &x);
        if(x){
            correct = 1;
        }
        printf("Input number = %d\n", x);
        // wait(NULL);
    }  
    
    return 0;
}