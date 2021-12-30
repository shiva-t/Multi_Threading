#ifndef __QUEUE__
#define __QUEUE__

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define QUEUE_SIZE 5

/*Data Structure to rep queue using array*/
struct queue {
    int front, rear,size; //size tells current occupancy of queue
    int capacity; //capacity tell max size of queue
    int *arr;
};

/*Function to initialise the queue*/
struct queue *queue_init(int capacity);

bool is_Empty(struct queue *q);

bool is_Full(struct queue *q);

void enqueue(struct queue *q, int num);

int dequeue(struct queue *q);

void queue_free(struct queue* q);

#endif
