#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_t thread_id1, thread_id2;

typedef struct
{
    char name[30];
    char birth[30];
    char phone[30];
    char hometown[30];
}thr_human;

static void *thr_handle(void *args)
{
    thr_human *thr = (thr_human *)args;
    pthread_t tid = pthread_self();
    if(pthread_equal(tid,thread_id1)){
        printf("Hello I'm thread 1\n");
    }
    else if (pthread_equal(tid,thread_id2)){
        pthread_join(thread_id1,NULL);
        printf("Hello I'm thread 2\n");
        printf("%s",thr->name);
        printf("%s",thr->birth);
        printf("%s",thr->phone);
        printf("%s",thr->hometown);
    }
}

int main(int argc, char *argv[]){
    thr_human human={0};
    int ret;

    strncpy(human.name,"Nguyen Lam Anh Vu\n",sizeof(human.name));
    strncpy(human.birth,"30/11/2003\n",sizeof(human.birth));
    strncpy(human.phone,"0949192027\n",sizeof(human.phone));
    strncpy(human.hometown,"TP.Buon Ma Thuot\n",sizeof(human.hometown));

    if(ret = pthread_create(&thread_id1,NULL,&thr_handle,NULL)){
        perror("pthread_create() 1 error");
        return -1;
    }
    if(ret = pthread_create(&thread_id2,NULL,&thr_handle,&human)){
        perror("pthread_create() 2 error");
        return -1;
    }
    sleep(1);
    return 0;
}
