#include "queue.h"

/*Function to initialise the queue*/
struct queue *queue_init(int capacity) {
    struct queue *q = (struct queue *)calloc(capacity, sizeof(struct queue));
    q->size = 0;
    q->rear = 0;
    q->front = 0;
    q->capacity = capacity;
    q->arr = (int *)calloc(capacity, sizeof(int));

    return q;
}

bool is_Empty(struct queue *q) {
    if(q->size == 0)
        return true;
    return false;
}

bool is_Full(struct queue *q) {
    if(q->size == q->capacity)
        return true;
    return false;
}

void enqueue(struct queue *q, int num) {
    if(is_Full(q)) {
       printf("Queue is full, enqueue failed\n");
       return;
    }

    q->rear = (q->rear + 1) % q->capacity;
    q->arr[q->rear] = num;
    q->size = q->size + 1;
    printf("Enqueue success for: %d\n", num);
    
}

int dequeue(struct queue *q) {
    if (is_Empty(q)) {
        printf("Queueis empty, dequeue failed\n");
        return INT_MIN;
    }
    int ret_val = 0;
    q->front = (q->front + 1) % q->capacity;
    ret_val = q->arr[q->front];
    q->size = q->size - 1;
    printf("Dequeue success: %d\n", ret_val);

    return ret_val;

}

void queue_free(struct queue* q) {
    free(q->arr);
    free(q);
}

