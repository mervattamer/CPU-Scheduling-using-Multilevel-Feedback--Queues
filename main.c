#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <Windows.h>
#include "structsfile.h"


// initializing constants
const int RR1_Quantum = 8;
const int RR2_Quantum = 16;
const int RR1_size = 10;
const int RR2_size = 20;
const int FCFS_size = 30 ;


// initializing queues and process
int p_num =0;
struct Queue* RR1;
struct Queue* RR2;
struct Queue* FCFS;
struct process p[100];

//function that works on process in queue 1
void rr1_fn(double queueTime)
{
    printf("WORKING ON QUEUE RR1\n");
    time_t startTime;
    time_t currentTime;
    double passed_time = 0.0;
    double rem_time = queueTime;
    time(&startTime); // start timing to make sure this queue takes 50% of cpu time



    while (passed_time < queueTime)  // if assigned queue time hasnt passed yet
    {

        while(!isEmpty(RR1)) // as long as there are process in queue
        {
            struct process x = dequeue(RR1);
            printf("starting process %d with burst %d\n", x.process_id, x.burst_time);


            if(x.burst_time> rem_time) //if the remaining cpu time for this queue is not enough to finish the process
            {
                if(rem_time<= RR1_Quantum ) //remaining cpu time is less than the queue quantum = 8
                {
                    Sleep(rem_time*1000); // subtract the remaining time from the process burst time
                    x.burst_time = x.burst_time - (rem_time/ 1);
                    enqueueFromFront(RR1, x);
                }
                else // if the
                {
                    Sleep(RR1_Quantum*1000); //subtract quantum from burst time of process and promote it
                    x.burst_time = x.burst_time - RR1_Quantum;
                    enqueue(RR2, x);
                    printf(" process %d promoted to RR2\n",x.process_id);

                }

            }

            else //if burst time pf process is less than or equal to remaining cpu time
            {

                if(x.burst_time <= RR1_Quantum ) // if burst time < quantum, wait until process complete
                {
                    Sleep(x.burst_time*1000);
                    printf(" process %d done\n",x.process_id);;
                }
                else
                {
                    Sleep(RR1_Quantum*1000); // if quantum<  burst time, wait until quantum time passes then promote process
                    x.burst_time = x.burst_time - RR1_Quantum;
                    enqueue(RR2, x);
                    printf(" process %d promoted to RR2\n",x.process_id);
                }


            }
            currentTime = time(NULL);
            passed_time = currentTime - startTime;
            rem_time = queueTime - passed_time; // check if remaining cpu time is equal to 0
            if (rem_time == 0)
                break;


        }
        currentTime = time(NULL);
        passed_time = currentTime - startTime;
        rem_time = queueTime - passed_time; // check remaining cpu time for this queue

    }
}

//function to work on third queue (fcfs)

void fcfs_fn(double queueTime)
{
    printf("WORKING ON QUEUE FCFS\n");
    time_t startTime;
    time_t curr_time;
    double passed_time = 0;
    double rem_time = queueTime;
    time(&startTime); // start time to make sure cpu time doesnt exceed 20%

    while (passed_time < queueTime) // if time not exceeded
    {
        while(!isEmpty(FCFS)) // and queue not empty
        {
            struct process x = dequeue(FCFS);
            printf("starting process %d with burst %d\n", x.process_id, x.burst_time);
            if(x.burst_time > rem_time ) //if not enough cpu time for this queue to finish process
            {
                Sleep(rem_time*1000);
                x.burst_time = x.burst_time - (rem_time/ 1);
                enqueueFromFront(FCFS, x);
            }
            else
            {
                Sleep(x.burst_time*1000); // wait till process complete
                //x.burst_time = 0;
                printf(" process %d done\n",x.process_id);

            }
            curr_time = time(NULL);
            passed_time = curr_time - startTime;
            rem_time = queueTime - passed_time;
            if (rem_time ==0) // check if there is remaining cpu time
            {
                break;
            }
        }
        curr_time = time(NULL);
        passed_time = curr_time - startTime;
        rem_time = queueTime - passed_time;

    }
}

//function to work on second roundrobin queue

void rr2_fn(double queueTime)
{
    printf("WORKING ON QUEUE RR2\n");
    time_t startTime;
    time_t curr_time;
    double passed_time = 0;
    double rem_time = queueTime;
    time(&startTime); // start time to make sure cpu time is 30% here

    while (passed_time < queueTime) // if cpu time for queue still not passed
    {

        while(!isEmpty(RR2)) // there are process in queue
        {
            struct process x = dequeue(RR2);
            printf("starting process %d with burst %d\n", x.process_id, x.burst_time);


            if(x.burst_time> rem_time) // if remaining cpu time for this queue not enough to finish process
            {
                if(rem_time <= RR2_Quantum )
                {
                    Sleep(rem_time*1000);
                    x.burst_time = x.burst_time - (rem_time/ 1);
                    enqueueFromFront(RR2, x);
                }
                // if quantum is greater than remaining and burst time, subtract quantum from burst time and promote or demote process
                else
                {
                   Sleep(RR2_Quantum*1000);
                    x.burst_time = x.burst_time - RR2_Quantum;
                    int promote_demote = rand()%10 + 1; // generate random number between 1 and 10
                    if (promote_demote >5) // promote if the number is greater than 5, ensures 50% promotion chance
                    {
                        enqueue(FCFS, x);
                        printf(" process %d promoted to FCFS\n",x.process_id);
                    }
                    else
                    {
                        enqueue(RR1, x); //demote chance is remaining 50%
                        printf(" process %d demoted to RR1\n",x.process_id);
                    }

                }

            }

            else
            {

                if(x.burst_time <= RR2_Quantum )
                {
                    Sleep(x.burst_time*1000); // if burst time is less than the quantum finish process
                    printf(" process %d done\n",x.process_id);

                }
                else
                {
                    Sleep(RR2_Quantum*1000);
                    x.burst_time = x.burst_time - RR2_Quantum;
                    int promote_demote = rand()%10 + 1;
                    if (promote_demote >5) //50% promotion probability
                    {
                        enqueue(FCFS, x);
                        printf(" process %d promoted to FCFS\n",x.process_id);
                    }
                    else
                    {
                        enqueue(RR1, x); //demote if number < 5, 50% demotion probability
                        printf(" process %d demoted to RR1\n",x.process_id);
                    }

                }


            }
            curr_time = time(NULL);
            passed_time = curr_time - startTime;
            rem_time = queueTime - passed_time;
            if (rem_time ==0) // check whether cpu should continue working on this queue or switch
            {
                break;
            }
        }
        curr_time = time(NULL);
        passed_time = curr_time - startTime;
        rem_time = queueTime - passed_time;


    }
}

int main()
{


    //creating queues and assigning their sizes

    RR1 = createQueue(RR1_size);
    RR2 = createQueue(RR2_size);
    FCFS = createQueue(FCFS_size);


    // creating the 100 process
    for( int i = 0; i<100 ; i++ )
    {
        p[i].process_id = i+1; // sequential process id
        p[i].burst_time = rand()%100 +1; // random burst time between 1 and 100

    }



    while(!isFull(RR1) )     //if there is place left for another process in first RR queue
    {
        enqueue(RR1, p[p_num]); // fill q1 with processes
        p_num++;
        printf(" process %d added to RR1\n",p_num);
    }


    //while all queues are not empty
    while(!isEmpty(RR1) || !isEmpty(RR2) || !isEmpty(FCFS) || p_num<20 )
    {


        // insert new process to RR1

        while(!isFull(RR1) && p_num<100)
        {
            enqueue(RR1, p[p_num]);
            p_num++;
            printf(" process %d added to RR1\n",p_num);
        }

        // cpu works on queues with divided time according to queue cpu time percentage
        rr1_fn(50);
        rr2_fn(30);
        fcfs_fn(20);



    }
}




