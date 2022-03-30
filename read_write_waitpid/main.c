#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

// #define OPEN_FAIL (1)
// #define FIFO_FAIL (2)
// #define WRITE_FAIL (3)

int main(int argc, char* argv[]){

    
    int fd[2];
    if(pipe(fd) == -1){
        return 1;
    }
    int pid = fork();

    if(pid == -1){return 2;}
    else if(pid == 0){
        int b;
        read(fd[0], &b, sizeof(int));
        b = b * 4;
        write(fd[1], &b, sizeof(int));
        exit(0);
    }
    else{
        int a = 5;
        write(fd[1], &a, sizeof(int));
        waitpid(pid, NULL, 0); // wait for specific child with process id pid, save exit status in second argument(NULL because we don't need that)
        read(fd[0], &a, sizeof(int));
        printf("Final a = %d\n", a);
    }

    return 0;
}