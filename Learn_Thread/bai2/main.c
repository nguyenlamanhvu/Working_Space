#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>

#include <sys/unistd.h>

pthread_t thread_id1, thread_id2, thread_id3;
int fd;
char buffer[300];
pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
typedef struct
{
    char name[30];
    char birth[30];
    char hometown[30];
}thr_human;
thr_human human;

static void *thr_handle1(void *args)
{
    thr_human *thr = (thr_human *)args;
    while (1)
    {
        sleep(1);
        pthread_mutex_lock(&lock1);
        //critical section 
        printf("Name:");
        fgets(human.name,sizeof(human.name),stdin);
        if(strcmp(human.name,"exit\n")==0){         //go exit de thoat
            exit(EXIT_SUCCESS);
        }
        human.name[strcspn(human.name, "\n")] = '\0';
        printf("Birth:");
        fgets(human.birth,sizeof(human.birth),stdin);
        human.birth[strcspn(human.birth, "\n")] = '\0';
        printf("Hometown:");
        fgets(human.hometown,sizeof(human.hometown),stdin);
        human.hometown[strcspn(human.hometown, "\n")] = '\0';

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock1);
    }  
    pthread_exit(NULL); // exit
}

static void *thr_handle2(void *args)
{
    thr_human *thr = (thr_human *)args;
    while (1)
    {
        pthread_mutex_lock(&lock1);
        // ready in advance when pthread_cond_signal() is called
        pthread_cond_wait(&cond, &lock1);

        fd=open("thongtinsinhvien.txt",O_CREAT|O_WRONLY|O_APPEND,0666);
        if(fd==-1){
            perror("open()");
            exit(EXIT_FAILURE);
        }

        int length=snprintf(buffer,sizeof(buffer),"%s | %s | %s\n",human.name,human.birth,human.hometown);
        printf("%d\n",length);

        ssize_t bytesWritten = write(fd, buffer, length);
        if (bytesWritten == -1) {
            perror("write()");
        }

        close(fd);
        pthread_cond_signal(&cond2);
        pthread_mutex_unlock(&lock1);
    } 
    pthread_exit(NULL); // exit
}


static void *thr_handle3(void *args)
{
    thr_human *thr = (thr_human *)args;
    while (1)
    {
        pthread_mutex_lock(&lock1);
        // ready in advance when pthread_cond_signal() is called
        pthread_cond_wait(&cond2, &lock1);

        fd=open("thongtinsinhvien.txt",O_RDONLY);
        if(fd==-1){
            perror("open()");
            exit(EXIT_FAILURE);
        }
        // Set con tro toi vi tri truoc ki tu '\n' o dong cuoi
        off_t currentPosition = lseek(fd, -2, SEEK_END);

        ssize_t bytesRead;

        // Ghi tung ki tu cho den khi gap ki tu '\n' o dong ke cuoi
        int i = 0;
        char c;
        while ((bytesRead = read(fd, &c, 1)) == 1 && c != '\n' && currentPosition >= 0) {
            buffer[i++] = c;
            currentPosition = lseek(fd, currentPosition - 1, SEEK_SET);
        }
        buffer[i] = '\n';

        // Switch chuoi
        int j = 0;
        int k = i - 1;
        while (j < k) {
            char temp = buffer[j];
            buffer[j] = buffer[k];
            buffer[k] = temp;
            j++;
            k--;
        }
        printf("%s",buffer);
        close(fd);
        pthread_mutex_unlock(&lock1);
    }
    pthread_exit(NULL); // exit
}

int main(int argc, char *argv[]){
    int ret;
    
    if(ret = pthread_create(&thread_id3,NULL,&thr_handle3,&human)){
        perror("pthread_create() 3 error");
        return -1;
    }
    if(ret = pthread_create(&thread_id2,NULL,&thr_handle2,NULL)){
        perror("pthread_create() 2 error");
        return -1;
    }
    if(ret = pthread_create(&thread_id1,NULL,&thr_handle1,NULL)){
        perror("pthread_create() 1 error");
        return -1;
    }
    
    // used to block for the end of a thread and release
    pthread_join(thread_id1,NULL);  
    pthread_join(thread_id2,NULL);
    pthread_join(thread_id3,NULL);
    return 0;
}