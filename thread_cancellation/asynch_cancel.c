/*
 #######################
 Author      : Shiva Tripathi
 Description : Implementation of Asynchoronous thread cancellation
               using Pthreads 
               Total three threads writing to different files
               User can cancel them asynch
 #######################
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void *write_routine(void *arg) {
    int *i = (int *)arg;
    char msg_write[32];
    char file_name[32];
    FILE *fptr;
    int n = 0, rc = 0;
    n = sprintf(file_name, "text_%d.txt", *i);
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, 0);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, 0);
    fptr = fopen(file_name, "w");
    if (!fptr) {
        printf("fopen failed\n");
        return 0;
    }
    
    while(1) {
        n = sprintf(msg_write, "Text written by thread: %d\n", *i);
        fwrite(msg_write, sizeof(char), n, fptr);
        fflush(fptr);
        sleep(1);
    }
}

int main() {
    int rc = 0 ,i = 0, id = 0;
    int *arg = NULL;
    pthread_t thread[3];
    for(i = 0; i < 3; i++) {
        arg = (int *) calloc(1, sizeof(int));
        *arg = i;
        rc = pthread_create(&thread[i],
                            NULL,
                            write_routine,
                            (void *)arg);
        if(rc != 0) {
            printf("Thread creation failed for : %d\n",i);
        }
    }
    while(1) {
        printf("Enter the thread ID <0-2> to be cancelled :\n");
        scanf("%d", &id);
        if(id<3 && id > -1) {
            pthread_cancel(thread[id]);
        } else { 
        printf("Invalid ID\n");
        }
    }

    pthread_exit(0);
    free(arg);
    return 0;
}
