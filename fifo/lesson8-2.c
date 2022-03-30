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

    int arr[5];

    int i;
    for(i = 0; i < 5; i++){
        arr[i] = i;
        // printf("%d", arr[i]);
    }
    printf("Begin\n");
    // if(mkfifo("sum", 0777) == -1){
    //     if(errno != EEXIST){return 2;}
    // }
    int fd = open("sum", O_WRONLY);
    if(fd == -1){return 1;}

    write(fd, arr, sizeof(int)*5);

    // for(i = 0; i < 5; i++){
    //     if(write(fd, &arr[i], sizeof(int)) == -1){
    //         printf("Error Writing to pipe");
    //         return 3;
    //     }
    //     printf("Wrote %d\n", arr[i]);
    // }
    close(fd);

    return 0;
}