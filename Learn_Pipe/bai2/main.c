#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define BUFFER_SIZE 20
char buffer[BUFFER_SIZE];
int fds[2];
const char *MSG1="I'm message 1\n";
const char *MSG2="I'm message 2\n";
const char *MSG3="I'm message 3\n";
__pid_t child_pid;
ssize_t num_read,num_write;

void sig_handler(int signum){
    printf("I'm sig_handler\n");
    wait(NULL);
}

int main(int argc, char *argv[]){
    if(pipe(fds)==-1){
        perror("pipe()");
        exit(EXIT_FAILURE);
    }
    child_pid=fork();
    if(child_pid>=0){
        if(child_pid==0){       //process con
            printf("I'm child process\n");
            // if(close(fds[0])==-1){      //close reader
            //     perror("close() child");
            //     exit(EXIT_FAILURE);
            // }
            if(close(fds[1])==-1){      //close writer
                perror("close() child");
                exit(EXIT_FAILURE);
            }
            int i=0;
            while (1)
            {
                num_read=read(fds[0],buffer,BUFFER_SIZE);
                if(num_read<0){
                    perror("read()");
                    exit(EXIT_FAILURE);
                } else if(num_read==0){
                    printf("reach to end_of_pipe\n");
                    break;
                } else{
                    printf("MSG[%d]: %s",i+1,buffer);
                }
            }    
            
        }
        else{                   //process cha
            signal(SIGCHLD,sig_handler);
            printf("I'm parent process\n");
            if(close(fds[0])==-1){      //close reader
                perror("close() child");
                exit(EXIT_FAILURE);
            }

            write(fds[1],MSG1,BUFFER_SIZE);
            write(fds[1],MSG2,BUFFER_SIZE);
            write(fds[1],MSG3,BUFFER_SIZE);

            if(close(fds[1])==-1){      //close writer
                perror("close() child");
                exit(EXIT_FAILURE);
            }
            while(1);
        }
    }
    else{
        perror("fork()");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}