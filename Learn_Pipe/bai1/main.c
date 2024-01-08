#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#define BUFFER_SIZE 20
char buffer[BUFFER_SIZE];
int fds[2];
const char *MSG1="I'm message 1\n";
const char *MSG2="I'm message 2\n";
const char *MSG3="I'm message 3\n";

int main(int argc, char *argv[]){
    if(pipe(fds)==-1){
        perror("pipe()");
        exit(EXIT_FAILURE);
    }
    write(fds[1],MSG1,BUFFER_SIZE);
    write(fds[1],MSG2,BUFFER_SIZE);
    write(fds[1],MSG3,BUFFER_SIZE);

    for(int i=0;i<3;i++){
        read(fds[0],buffer,BUFFER_SIZE);
        printf("MSG[%d]: %s",i+1,buffer);
    }

    exit(EXIT_SUCCESS);
}