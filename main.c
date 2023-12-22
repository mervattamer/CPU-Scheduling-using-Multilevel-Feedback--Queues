#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
const int RR1_Quantum = 8;
const int RR2_Quantum = 16;
const int RR1_size = 10;
const int RR2_size = 20;
const int FCFS_size = 20 ;

struct process
{
    int process_id;
    int burst_time;
};


// A structure to represent a queue
struct Queue {
    int front, rear, size;
    int capacity;
    struct process* array;
};

// function to create a queue
// of given capacity.
// It initializes size of queue as 0
struct Queue* createQueue(int capacity)
{
    struct Queue* queue = (struct Queue*)malloc(
        sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;

    // This is important, see the enqueue
    queue->rear = capacity - 1;
    queue->array = (struct process*)malloc(
        queue->capacity * sizeof(struct process));
    return queue;
}

// Queue is full when size becomes
// equal to the capacity
int isFull(struct Queue* queue)
{
    return (queue->size == queue->capacity);
}

// Queue is empty when size is 0
int isEmpty(struct Queue* queue)
{
    return (queue->size == 0);
}

// Function to add an item to the queue.
// It changes rear and size
void enqueue(struct Queue* queue, struct process item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1)
                  % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
   // printf("%d enqueued to queue\n", item);
}

// Function to remove an item from queue.
// It changes front and size
struct process dequeue(struct Queue* queue)
{
    //if (isEmpty(queue))
      //  return INT_MIN;
    struct process item = queue->array[queue->front];
    queue->front = (queue->front + 1)
                   % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

struct Queue* RR1;
struct Queue* RR2;
struct Queue* FCFS;

void rr1_fn()
{
    struct process x = dequeue(RR1);
        if(x.burst_time<= RR1_Quantum)
        {
            sleep(x.burst_time);
            x.burst_time = 0;
            printf(" process %d done\n",x.process_id);

            //enqueue(RR1, p[i]);
            //i++;

        }
        else
        {
            sleep(RR1_Quantum);
            x.burst_time = x.burst_time - RR1_Quantum;
            //enqueue(RR1, x);
            int promote_demote = rand()%10 +1;
            if( promote_demote > 5)
            {
                enqueue(RR2, x);
                printf(" process %d added to RR2\n",x.process_id);
            }
            else{
                    enqueue(RR1, x);
                    printf(" process %d added to RR1 again\n",x.process_id);
            // promote or demote
            }
        }
}
void fcfs_fn()
{
    while(!isEmpty(FCFS))
    {
      struct process x = dequeue(FCFS);
      sleep(x.burst_time);
    }

}

void rr2_fn()
{
    struct process x = dequeue(RR2);
        if(x.burst_time<= RR2_Quantum)
        {
            sleep(x.burst_time);
            x.burst_time = 0;

        }
        else
        {
            x.burst_time = x.burst_time - RR2_Quantum;
            sleep(RR2_Quantum);

            int promote_demote = rand()%100 +1;
            if( promote_demote > 50)
            {
                enqueue(FCFS, x);
            }
            else
                    enqueue(RR1, x);

            // promote or demote

        }


}

int main()
{
    struct process p[100];

    //initializing rr1

    RR1 = createQueue(RR1_size);

    //initializing rr2
    RR2 = createQueue(RR2_size);


    FCFS = createQueue(FCFS_size);


    for( int i = 0; i<100 ;i++ )
    {
        p[i].process_id = i+1;
        p[i].burst_time = rand()%20 +1; // change this to rand only

    }


    int i =0;
    while(!isFull(RR1) )     //if there is place left for another process in first RR queue
        {
            enqueue(RR1, p[i]); // fill q1 with processes
            i++;
        }
    //int j = 0;
    //while all queues are not empty
    while(i<20)
    {
        struct process x = dequeue(RR1);
        if(x.burst_time<= RR1_Quantum)
        {
            sleep(x.burst_time);
            x.burst_time = 0;
            printf(" process %d done\n",x.process_id);

            //enqueue(RR1, p[i]);
            //i++;

        }
        else
        {
            sleep(RR1_Quantum);
            x.burst_time = x.burst_time - RR1_Quantum;
            //enqueue(RR1, x);
            int promote_demote = rand()%10 +1;
            if( promote_demote > 5)
            {
                enqueue(RR2, x);
                printf(" process %d added to RR2\n",x.process_id);
            }
            else{
                    enqueue(RR1, x);
                    printf(" process %d added to RR1 again\n",x.process_id);
            // promote or demote
            }
        }

        while(!isFull(RR1) )
        {
            enqueue(RR1, p[i]);
            i++;
        }
        printf(" process %d added to RR1\n",i);
    }
}




