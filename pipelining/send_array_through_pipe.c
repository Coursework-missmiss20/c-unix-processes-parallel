#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

int main(){
    int fd[2];
    if(pipe(fd) == -1){return 2;}

    int pid = fork();
    if(pid == -1){return 1;}

    if(pid == 0){
        close(fd[0]);
        int arr[10];
        srand(time(NULL));
        int n = rand() % 10 + 1;
        for(int i = 0; i < n; i++){
            arr[i] = rand() % 11;
        }
        if(write(fd[1], &n, sizeof(int)) < 0){return 3;}
        if(write(fd[1], arr, sizeof(int) * n) < 0){return 3;}
        close(fd[1]);
        
        for(int i = 0; i < n; i++){
            printf("%d\n", arr[i]);
        }
    }
    else{
        close(fd[1]);
        int n;
        int arr[10];
        if(read(fd[0], &n, sizeof(int)) < 0){return 3;}
        if(read(fd[0], arr, sizeof(int) * n) < 0){return 3;}

        int sum = 0;
        for(int i = 0; i < n; i++){
           sum += arr[i];
        }
        printf("Sum = %d\n", sum);
        close(fd[0]);  
    }
    return 0;
}

