#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    __pid_t pidB = fork(),w;
    __pid_t pidB_child;
    int wstatusB,wstatusB_child;
    if(pidB >= 0){
        if(pidB == 0){ //process B
            pidB_child = fork();
            if(pidB_child >= 0){        
                if(pidB_child == 0){
                    printf("Hello I'm process B'\n");
                }
                else{
                    w=waitpid(pidB_child,&wstatusB_child, WUNTRACED);       //pid
                    if(w==-1){
                        perror("waitpid() error");
                        exit(EXIT_FAILURE);
                    }
                    else{
                        printf("Hello I'm Process B\n");
                    }
                }
            }
            else{
                perror("folk() error");
                exit(EXIT_FAILURE);
            }
        }
        else{       //process A
            w=waitpid(pidB,&wstatusB, WUNTRACED);       //pid
            if(w==-1){
                perror("waitpid() error");
                exit(EXIT_FAILURE);
            }
            else{
                printf("Hello I'm Process A\n");
            }
        }
    }
    else{
        perror("folk() error");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
