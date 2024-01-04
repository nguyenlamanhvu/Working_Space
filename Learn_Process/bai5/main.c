#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
void func(int signum){
    printf("Have SIGCHLD signal\n");
    wait(NULL);     //cho bat ky process con nao
}
int main(int argc, char *argv[])
{
    __pid_t child_pid = fork();
    int w;
    if(child_pid >= 0){
        if(child_pid == 0){ //process B
            printf("Process A ID: %d, Process B ID: %d\n",getppid(),getpid());
            while(1);
        }
        else{       //process A
            signal(SIGCHLD,func);
            printf("Process A\n");
            while(1);
        }
    }
    else{
        perror("folk() error");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
