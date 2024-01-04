#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    __pid_t child_pid = fork(),w;
    int wstatus;
    if(child_pid >= 0){
        if(child_pid == 0){ //process B
            printf("Process A ID: %d, Process B ID: %d\n",getppid(),getpid());
        }
        else{       //process A
            sleep(3);
            w=waitpid(child_pid,&wstatus, WUNTRACED);       //pid
            if(w==-1){
                perror("waitpid() error");
                exit(EXIT_FAILURE);
            }
            else{
                printf("Process B status: %d\n",wstatus);
            }
        }
    }
    else{
        perror("folk() error");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
