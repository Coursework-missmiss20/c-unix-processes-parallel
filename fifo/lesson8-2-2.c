#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char* argv[]){

    printf("Begin\n");
    int arr[5];
    int i = 0;
    int fd = open("sum", O_RDONLY);
    if(fd == -1){return 1;}

    printf("Begin to read\n");
    // 一次性读5个
    // read(fd, arr, sizeof(int)*5);
    // for(i = 0; i < 5; i++){
    //     printf("Received %d\n", arr[i]);
    // }
    // 分五次读五个，两个有同样的效果
    for(i = 0; i < 5; i++){
        if(read(fd, &arr[i], sizeof(int)) == -1){
            return 2;
        }
        printf("Received %d\n", arr[i]);
    }
    close(fd);



    return 0;
}