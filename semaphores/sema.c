/*
  Author        : Shiva Tripathi
  Description   : Sample code for using semaphores
                  Critical Section is array
                  Total 5 threads are present trying to access C.S. periodically and
                  only 2 can access the CS at a time, acheived using semaphores 
  Keywords      : posix, multithreading, semaphores
  Steps to exec : gcc -g -c sema.c -o sema.o
                  gcc -g sema.o -o sema.exe -lpthread
 */

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define SEM_LIMIT 2
sem_t sem;
int arr[5];

void *routine(void *arg) {
    int id = (int *)arg;
    int i = 0, sum = 0;

    while(1) {
        printf("C.S. P() by thread: %d\n", id);
        sem_wait(&sem);
        /*CS*/
        sum = 0;
        for(i = 0; i<5 ; i++) {
            sum = sum + arr[i];
        }
        printf("Critical section accessed by thread: %d\n", id);
        sleep(1.5);
        sem_post(&sem);
        printf("C.S. V() by thread: %d\n", id);
        sleep(2);
    }
}

void thread_create(void) {
    int rc = 0, i = 0;
    pthread_t threads[5];

    for (i = 0; i <5; i++) {
        rc = pthread_create(&threads[i],
                            NULL,
                            routine,
                            (void *) i);
        if (rc != 0) {
            printf("thread creation failed for :%d\n", i);
        }
    }
}

void init_arr(void) {
    int i;
    for(i = 0; i<5; i++) {
        arr[i] = i;
    }
}

int main() {
    init_arr();
    sem_init(&sem, 0, SEM_LIMIT);
    thread_create();
    pthread_exit(0);

    return 0;
}
