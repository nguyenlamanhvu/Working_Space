#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sig_handler1(int signum){
    printf("Received SIGINT\n");
}
void sig_handler2(int signum){
    printf("Received SIGUSR1\n");
}
void sig_handler3(int signum){
    printf("Received SIGUSR2\n");
}

int main(int argc,char *argv[]){
    if(signal(SIGINT,sig_handler1)==SIG_ERR){
        perror("Cannot handle SIGINT\n");
        exit(EXIT_FAILURE);
    }
    if(signal(SIGUSR1,sig_handler2)==SIG_ERR){
        perror("Cannot handle SIGUSR1\n");
        exit(EXIT_FAILURE);
    }
    if(signal(SIGUSR2,sig_handler3)==SIG_ERR){
        perror("Cannot handle SIGUSR2\n");
        exit(EXIT_FAILURE);
    }
    while(1){
        printf("Progam is running\n");
        sleep(1);
    }
    exit(EXIT_SUCCESS);
}