#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <Windows.h>
#include "structsfile.h"

const int RR1_Quantum = 8;
const int RR2_Quantum = 16;
const int RR1_size = 10;
const int RR2_size = 20;
const int FCFS_size = 30 ;



int p_num =0;
struct Queue* RR1;
struct Queue* RR2;
struct Queue* FCFS;
struct process p[100];


void rr1_fn(double queueTime)
{
    printf("WORKING ON QUEUE RR1\n");
    time_t startTime;
    time_t currentTime;
    double passed_time = 0.0;
    double rem_time = queueTime;
    time(&startTime);
    //printf("set time = %f\n", setTime);
    //printf("start time = %ld\n", startTime);


    while (passed_time < queueTime)
    {

        while(!isEmpty(RR1))
        {
            struct process x = dequeue(RR1);
            printf("starting process %d with burst %d\n", x.process_id, x.burst_time);


            if(x.burst_time> rem_time)
            {
                if(rem_time<= RR1_Quantum )
                {
                    Sleep(rem_time*1000);
                    x.burst_time = x.burst_time - (rem_time/ 1);
                    enqueueFromFront(RR1, x);
                }
                else
                {
                    Sleep(RR1_Quantum*1000);
                    x.burst_time = x.burst_time - RR1_Quantum;
                    enqueue(RR2, x);
                    printf(" process %d promoted to RR2\n",x.process_id);

                }

            }

            else
            {

                if(x.burst_time <= RR1_Quantum )
                {
                    Sleep(x.burst_time*1000);
                    printf(" process %d done\n",x.process_id);;
                }
                else
                {
                    Sleep(RR1_Quantum*1000);
                    x.burst_time = x.burst_time - RR1_Quantum;
                    enqueue(RR2, x);
                    printf(" process %d promoted to RR2\n",x.process_id);
                }


            }
            currentTime = time(NULL);
            passed_time = currentTime - startTime;
            rem_time = queueTime - passed_time;
            if (rem_time == 0)
                break;
            //printf("remaining time = %f\n", rem_time);

        }
        currentTime = time(NULL);
        passed_time = currentTime - startTime;
       // printf("elapsed time = %f\n",elapsedTime);
        rem_time = queueTime - passed_time;

    }
}

void fcfs_fn(double queueTime)
{
    printf("WORKING ON QUEUE FCFS\n");
    time_t startTime;
    time_t curr_time;
    double passed_time = 0;
    double rem_time = queueTime;
    time(&startTime);

    while (passed_time < queueTime)
    {
        while(!isEmpty(FCFS))
        {
            struct process x = dequeue(FCFS);
            printf("starting process %d with burst %d\n", x.process_id, x.burst_time);
            if(x.burst_time > rem_time )
            {
                Sleep(rem_time*1000);
                x.burst_time = x.burst_time - (rem_time/ 1);
                enqueueFromFront(FCFS, x);
            }
            else
            {
                Sleep(x.burst_time*1000);
                //x.burst_time = 0;
                printf(" process %d done\n",x.process_id);
                /*if(p_num<100)
                {
                    enqueue(RR1, p[p_num]);
                    p_num++;
                }*/

            }
            curr_time = time(NULL);
            passed_time = curr_time - startTime;
            rem_time = queueTime - passed_time;
            if (rem_time ==0)
            {
                break;
            }
        }
        curr_time = time(NULL);
        passed_time = curr_time - startTime;
        rem_time = queueTime - passed_time;

    }
}

void rr2_fn(double queueTime)
{
    printf("WORKING ON QUEUE RR2\n");
    time_t startTime;
    time_t curr_time;
    double passed_time = 0;
    double rem_time = queueTime;
    time(&startTime);

    while (passed_time < queueTime)
    {

        while(!isEmpty(RR2))
        {
            struct process x = dequeue(RR2);
            printf("starting process %d with burst %d\n", x.process_id, x.burst_time);


            if(x.burst_time> rem_time)
            {
                if(rem_time <= RR2_Quantum )
                {
                    Sleep(rem_time*1000);
                    x.burst_time = x.burst_time - (rem_time/ 1);
                    enqueueFromFront(RR2, x);
                }
                else
                {
                   Sleep(RR2_Quantum*1000);
                    x.burst_time = x.burst_time - RR2_Quantum;
                    int promote_demote = rand()%10 + 1;
                    if (promote_demote >5)
                    {
                        enqueue(FCFS, x);
                        printf(" process %d promoted to FCFS\n",x.process_id);
                    }
                    else
                    {
                        enqueue(RR1, x);
                        printf(" process %d demoted to RR1\n",x.process_id);
                    }

                }

            }

            else
            {

                if(x.burst_time <= RR2_Quantum )
                {
                    Sleep(x.burst_time*1000);
                    printf(" process %d done\n",x.process_id);

                }
                else
                {
                    Sleep(RR2_Quantum*1000);
                    x.burst_time = x.burst_time - RR2_Quantum;
                    int promote_demote = rand()%10 + 1;
                    if (promote_demote >5)
                    {
                        enqueue(FCFS, x);
                        printf(" process %d promoted to FCFS\n",x.process_id);
                    }
                    else
                    {
                        enqueue(RR1, x);
                        printf(" process %d demoted to RR1\n",x.process_id);
                    }

                }


            }
            curr_time = time(NULL);
            passed_time = curr_time - startTime;
            rem_time = queueTime - passed_time;
            if (rem_time ==0)
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


    //initializing queues

    RR1 = createQueue(RR1_size);
    RR2 = createQueue(RR2_size);
    FCFS = createQueue(FCFS_size);


    for( int i = 0; i<100 ; i++ )
    {
        p[i].process_id = i+1;
        p[i].burst_time = rand()%100 +1; // change this to rand only

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


        while(!isFull(RR1) && p_num<20 )
        {
            enqueue(RR1, p[p_num]);
            p_num++;
            printf(" process %d added to RR1\n",p_num);
        }

        rr1_fn(50);
        rr2_fn(30);
        fcfs_fn(20);



    }
}




