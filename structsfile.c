#include "structsfile.h"


struct Queue* createQueue(int Qsize)
{
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->Qsize = Qsize;
    queue->size = 0;
    queue->front = 0;
    queue->rear = Qsize - 1;
    queue->array = (struct process*)malloc(queue->Qsize * sizeof(struct process));
    return queue;
}


int isFull(struct Queue* queue)
{
    return (queue->size == queue->Qsize);
}

int isEmpty(struct Queue* queue)
{
    return (queue->size == 0);
}

void enqueue(struct Queue* queue, struct process p)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->Qsize;
    queue->array[queue->rear] = p;
    queue->size = queue->size + 1;
}

struct process dequeue(struct Queue* queue)
{
    struct process p = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->Qsize;
    queue->size = queue->size - 1;
    return p;
}

void enqueueFromFront(struct Queue* queue, struct process p)
{
    if (isFull(queue))
        return;
    queue->front = (queue->front - 1 + queue->Qsize) % queue->Qsize;
    queue->array[queue->front] = p;
    queue->size = queue->size + 1;
}
