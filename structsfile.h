#ifndef STRUCTSFILE_H_INCLUDED
#define STRUCTSFILE_H_INCLUDED

struct process
{
    int process_id;
    int burst_time;
};
// A structure to represent a queue
struct Queue
{
    int front;
    int rear;
    int size;
    int Qsize;
    struct process* array;
};


struct Queue* createQueue(int Qsize);
int isFull(struct Queue* queue);
int isEmpty(struct Queue* queue);
void enqueue(struct Queue* queue, struct process p);
struct process dequeue(struct Queue* queue);
void enqueueFromFront(struct Queue* queue, struct process p);

#endif // STRUCTSFILE_H_INCLUDED
