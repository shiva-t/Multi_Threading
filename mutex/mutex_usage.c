/*
  Author        : Shiva Tripathi
  Description   : Sample code to acheive mutual exclusion 
                  using mutex - posix threads
                  Critical Section is an array, producer swaps 2 array elements
                  consumer just reads and sums them
  Keywords      : posix, multithreading, mutex
  Steps to exec : gcc -g -c mutex_usage.c -o mutex_usage.o
                  gcc -g mutex_usage.o -o mutex_usage.exe -lpthread
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define ARR_SIZE 4

int arr[ARR_SIZE];
pthread_mutex_t mut;

/*function to initialise array*/
void arr_init(void) {
   int i;
   for (i = 0; i < ARR_SIZE; i++) {
       arr[i] = i;
   }
}

void *cons_routine(void *arg) {
   int i = 0, sum = 0;
   while(1) {
       pthread_mutex_lock(&mut);
       /*C.S. read*/
       sum = 0;
       for(i = 0; i< ARR_SIZE; i++) {
           sum = sum+arr[i];
       }
       printf("consumer accessing critical section- sum: %d\n", sum);
       pthread_mutex_unlock(&mut);
       sleep(1.5); //consumer tried to read after every 1.5 sec
    }
}

void swap(int *t1, int *t2) {
    int tmp;
    tmp = *t1;
    *t1 = *t2;
    *t2 = tmp;
}

void *prod_routine(void *arg) {
    while(1) {
        pthread_mutex_lock(&mut);
        printf("prod swapping the elements\n");
        swap(&arr[0], &arr[1]);
        pthread_mutex_unlock(&mut);
        sleep(1.5);
    }
}

/*function to create consumer and producer thread*/
void threads_creation(void) {
    int rc = 0;
    pthread_t thread_cons;
    pthread_t thread_prod;

    rc = pthread_create(&thread_prod,
                        NULL,
                        prod_routine,
                        NULL);
    if (rc != 0) {
        printf("Thread cration falied for producer\n");
        return;
    } 

    rc = pthread_create(&thread_cons,
                        NULL,
                        cons_routine,
                        NULL);
    if (rc != 0) {
        printf("Thread cration falied for consumer\n");
        return;
    }

}

/*MAIN*/
int main(int argc, char *argv[]) {
    pthread_mutex_init(&mut, NULL);
    arr_init();
    threads_creation();
    pthread_exit(0); //prog continues while main terminates
    return 0;
}

