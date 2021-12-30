/*
  Author        : Shiva Tripathi <shivat.offical@gmail.com>
  Description   : Sample code for using condition variables with mutex
                  Critical Section is queue, producer performs enqueue
                  consumer performs dequeue, so mutex is needed with signalling mechanism
                  consumers performs read only when producer thread sends signal
  Keywords      : posix, multithreading, mutex, conditional variables
  Steps to exec : gcc -g -c cond_var.c -o cond_var.o
                  gcc -g cond_var.o -o cond_var.exe -lpthread
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "queue.h"

struct queue *q_s = NULL;
pthread_mutex_t mut;
pthread_cond_t cv;
pthread_t thread[2];

void *cons_routine(void *arg) {
    int i = 0;
    while (1) {
        pthread_mutex_lock(&mut);
        printf("consumer: acquired mutex\n");
        pthread_cond_wait(&cv, &mut);
        printf("consumer: received signal, acessing queue\n");
        for (i = 0; i <= QUEUE_SIZE; i++)
        {
            printf("consumer: %d\n", dequeue(q_s));    
        }
        pthread_mutex_unlock(&mut);
        printf("\n");
        sleep(1.5);
    }
}

void *prod_routine(void *arg) {
    int i = 0;
    while (1) {
        pthread_mutex_lock(&mut);
        printf("producer: acquired mutex\n");
        for (i = 0; i < QUEUE_SIZE; i++)
        {
            enqueue(q_s, i);        
        }
        pthread_cond_signal(&cv);
        printf("producer: sending signal for cv\n\n");
        pthread_mutex_unlock(&mut);
        sleep(1.5);
    }
}

void create_threads(void) {
    int rc = 0;
    rc = pthread_create(&thread[0],
                        NULL,
                        cons_routine,
                        NULL);
    if (rc != 0) {
        printf("cons thread creation failed\n");
        return;
    }

    rc = pthread_create(&thread[1],
                        NULL,
                        prod_routine,
                        NULL);
    if (rc != 0) {
        printf("prod thread creation failed\n");
        return;
    }
}

int main() {
    q_s = queue_init(QUEUE_SIZE);
    create_threads();

    /*main waits for threads to terminate*/
    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);
    queue_free(q_s);
    return 0;
}

