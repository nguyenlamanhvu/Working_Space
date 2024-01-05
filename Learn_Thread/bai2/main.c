#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
pthread_t thread_id1, thread_id2, thread_id3;
int fd;
char str[100],str2[100];
pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

typedef struct
{
    char name[30];
    char birth[30];
    char hometown[30];
}thr_human;
thr_human human={0};

static void *thr_handle1(void *args)
{
    sleep(1);
    thr_human *thr = (thr_human *)args;
    pthread_mutex_lock(&lock1);
    //critical section 
    printf("Name:");
    fgets(human.name,sizeof(human.name),stdin);
    printf("Birth:");
    fgets(human.birth,sizeof(human.birth),stdin);
    printf("Hometown:");
    fgets(human.hometown,sizeof(human.hometown),stdin);

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock1);

    pthread_exit(NULL); // exit
    
}

static void *thr_handle2(void *args)
{
    thr_human *thr = (thr_human *)args;
    fd=open("thongtinsinhvien.txt",O_CREAT|O_RDWR,0666);
    if(fd==-1){
        perror("open()");
        exit(EXIT_FAILURE);
    }
    pthread_mutex_lock(&lock1);
    // ready in advance when pthread_cond_signal() is called
    pthread_cond_wait(&cond, &lock1);
    write(fd,"Name: ",strlen("Name: "));
    strncpy(str,human.name,strlen(human.name)-1);
    write(fd,str,sizeof(str));
    write(fd,",Birth: ",strlen("Birth: "));
    strncpy(str2,human.birth,strlen(human.birth)-1);
    write(fd,str2,sizeof(str2));
    write(fd,",Hometown: ",strlen("Hometown: "));
    write(fd,human.hometown,sizeof(human.hometown));

    close(fd);
    pthread_mutex_unlock(&lock1);
    pthread_exit(NULL); // exit
}

// static void *thr_handle3(void *args)
// {
//     thr_human *thr = (thr_human *)args;
    
// }

int main(int argc, char *argv[]){
    int ret;
    
    if(open("thongtinsinhvien.txt", O_RDWR|O_CREAT,0666)==-1){
        perror("open() error");
        return -1;
    }

    if(ret = pthread_create(&thread_id1,NULL,&thr_handle1,NULL)){
        perror("pthread_create() 1 error");
        return -1;
    }
    if(ret = pthread_create(&thread_id2,NULL,&thr_handle2,NULL)){
        perror("pthread_create() 2 error");
        return -1;
    }
    // if(ret = pthread_create(&thread_id3,NULL,&thr_handle3,&human)){
    //     perror("pthread_create() 2 error");
    //     return -1;
    // }
    // used to block for the end of a thread and release
    pthread_join(thread_id1,NULL);  
    pthread_join(thread_id2,NULL);
    // pthread_join(thread_id3,NULL);
    return 0;
}