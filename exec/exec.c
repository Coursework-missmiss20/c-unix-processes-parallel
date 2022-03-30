#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


// #define OPEN_FAIL (1)
// #define FIFO_FAIL (2)
// #define WRITE_FAIL (3)

// execlp: execut, a list of arguments, path
int main(int argc, char* argv[]){

    int pid = fork();
    if(pid == -1){return 1;}
    else if(pid == 0){
        char arr[] = {
            "ping",
            "-c",
            "3",
            "google.com",
            NULL
        };
        // system("pwd");
        // execlp("/bin/pwd", "pwd", NULL);
        // execlp("ping","ping","-c","3","google.com",NULL);
        execvp("ping",arr);
    }
    else{
        int wstatus;
        // save the exit status 
        wait(&wstatus);
        if(WIFEXITED(wstatus)){
            int statusCode = WEXITSTATUS(wstatus);
            if(statusCode == 0){ printf("Success\n");}
            else{printf("Failure\n");}
        }
    }
    return 0;
}


// dup(fd1), make new fd and point to fd1
// dup2(fd, 1), whatever pointed to 1, point it to fd now. (change stdout to somthing else)
// close(fd)