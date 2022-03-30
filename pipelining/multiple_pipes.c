#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define PROCESS_NUM (3)

// three pipes loop
int main(){
    int fds[PROCESS_NUM+1][2];
    int pids[PROCESS_NUM];
    int i;
    // create all pipes
    for(i = 0; i < PROCESS_NUM+1; i++){
        if(pipe(fds[i]) < 0){return 1;}
    }
    // forking processes
    for(i = 0;i < PROCESS_NUM; i++){
        pids[i] = fork();
        if(pids[i] < 0){printf("Error fork()\n");return 2;}
        // child process
        if(pids[i] == 0){
            int j;
            // child process close unnecessary pipes
            for(j = 0; j < PROCESS_NUM+1; j++){
                if(i != j){
                    close(fds[j][0]);
                }
                if(i+1 != j){
                    close(fds[j][1]);
                }
            }
            int x;
            if(read(fds[i][0], &x, sizeof(int)) < 0){printf("Error read()\n");return 3;}
            printf("(%d) got %d\n", i, x);
            x = x + 1;
            if(write(fds[i+1][1], &x, sizeof(int)) < 0){printf("Error write()\n");return 4;}
            printf("(%d) sent %d\n", i, x);
            close(fds[i][0]);
            close(fds[i+1][1]);
            return 0;
        }
        // parent continue
    }
    int x = 5;
    printf("Main process sent %d\n", x);
    if(write(fds[0][1], &x, sizeof(int)) < 0){printf("Error write()\n");return 4;}
    if(read(fds[PROCESS_NUM][0], &x, sizeof(int)) < 0){printf("Error read()\n");return 3;}

    // wait for all child processes to finish
    for(i = 0;i < PROCESS_NUM; i++){
        wait(NULL);
    }
    printf("final result is %d\n", x);
    return 0;
}

