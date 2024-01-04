#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/file.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
int main(int argc, char *argv[])
{
    if(argc != 2){
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct stat sb;

    if (lstat(argv[1], &sb) == -1) {
       perror("lstat");
       exit(EXIT_FAILURE);
    }
    
    printf("File type:                ");
        switch (sb.st_mode & __S_IFMT ){
           case __S_IFBLK:  printf("block device\n");            break;
           case __S_IFCHR:  printf("character device\n");        break;
           case __S_IFDIR:  printf("directory\n");               break;
           case __S_IFIFO:  printf("FIFO/pipe\n");               break;
           case __S_IFLNK:  printf("symlink\n");                 break;
           case __S_IFREG:  printf("regular file\n");            break;
           case __S_IFSOCK: printf("socket\n");                  break;
           default:       printf("unknown?\n");                break;
        }
    printf("I-node number:            %ju\n", (uintmax_t) sb.st_ino);
    printf("Last status change:       %s", ctime(&sb.st_ctime));
    printf("Last file access:         %s", ctime(&sb.st_atime));
    printf("Last file modification:   %s", ctime(&sb.st_mtime));
    exit(EXIT_SUCCESS);
}
