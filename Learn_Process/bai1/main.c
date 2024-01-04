#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    __pid_t child_pid = fork();
    
    if(child_pid >= 0){
        if(child_pid == 0){
            printf("Process B\n");
            printf("Process A ID: %d, Process B ID: %d\n",getppid(),getpid());
            while(1);
        }
        else{
            printf("Process A\n");
            printf("Process A ID: %d, Process B ID: %d\n",getpid(),child_pid);
            sleep(1);
        }
    }
    else{
        perror("folk()\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
