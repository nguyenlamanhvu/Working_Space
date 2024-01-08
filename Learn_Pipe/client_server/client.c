#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_CLIENT "./fifo_client"
#define FIFO_SERVER "./fifo_server"

#define BUFFER_SIZE 1024
char buffer[BUFFER_SIZE];
int fd;

int main(int argc, char *argv[]){
    mkfifo(FIFO_CLIENT,0666);
    mkfifo(FIFO_SERVER,0666);
    
    while (1)
    {
        
    }
    
    exit(EXIT_SUCCESS);
}