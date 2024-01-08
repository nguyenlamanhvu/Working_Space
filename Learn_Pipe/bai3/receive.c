#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO "./myfifo"
#define BUFFER_SIZE 1024
char buffer[BUFFER_SIZE];
int fd;

int main(int argc, char *argv[]){
    mkfifo(FIFO,0666);
    while (1)
    {
        fd=open(FIFO,O_RDONLY);
        read(fd,buffer,BUFFER_SIZE);
        printf("Receive message:  %s",buffer);
        close(fd);
    }
    
    exit(EXIT_SUCCESS);
}