#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/wait.h>

void handle_terminate(int sig){
    printf("Terminate not allowed\n");
}

void handle_sigttstp(int sig){
    printf("Stop not allowed\n");
}

void handle_sigcout(int sig){
    printf("Input Number: ");
    fflush(stdout);
}

int main(int argc, char* argv[]){
    struct sigaction sa;
    sa.sa_handler = &handle_sigcout;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGCONT, &sa, NULL);

    int x;
    printf("Input Number: ");
    scanf("%d", &x);
    printf("Input number = %d\n", x);
    return 0;
}