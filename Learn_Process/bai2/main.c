#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char *argv[])
{
    __pid_t child_pid = fork();
    const char text[100]={"Hello Anh Vu\n"};
    char mem[100]={};
    if(child_pid >= 0){
        if(child_pid == 0){
            int fd=open("./log/hello.txt",O_RDWR);
            if(fd==-1){
                perror("open() error");
                exit(EXIT_FAILURE);
            }
            read(fd,mem,strlen(text));
            printf("String: %s",mem);
            close(fd);
        }
        else{
            int fd=open("./log/hello.txt",O_CREAT | O_RDWR,0666);
            if(fd==-1){
                perror("open() error");
                exit(EXIT_FAILURE);
            }
            write(fd,text,strlen(text));
            close(fd);
        }
    }
    else{
        perror("folk() error");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
