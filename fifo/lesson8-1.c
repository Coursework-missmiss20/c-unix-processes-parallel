#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

#define FORK_FAIL (1)
#define FIFO_FAIL (2)
#define WRITE_FAIL (3)

// FIFO和pipe类似，但是一端写，一端读同时发生，程序才会继续运行，如果只有读或只有写，那么
// FIFO会暂停运行
// 下面的code会在运行 line 22 后停止
// 此时在terminal中输入：<cat myfifo1>， 那么程序就将继续运行（读也开始了）
int main(int argc, char* argv[]){
    if(mkfifo("myfifo1", 0777) == -1){
        if(errno != EEXIST){return FIFO_FAIL;}
    }
    printf("Opening \n");
    int fd = open("myfifo1", O_WRONLY);
    char x = 'a';
    if(write(fd, &x, sizeof(x))){return WRITE_FAIL;}
    close(fd);
    return 0;
}