CPU SCHEDULING USING QUEUES

I. PROJECT DESCRIPTION:
This project is a C source code for implementing Multi-level feedback queue. Multilevel feedback queue is a scheduling algorithm. 

In general, the Multilevel feedback queue algorithm: 
1. Puts different processes into separate queues based on how much they need the CPU.
2. Promotes/demotes a process to different queues.
3. Gives more attention to processes that use the CPU quickly.
4. Gives priority to processes that do a lot of input/output (I/O) operations. If a process mainly uses I/O, it waits in a queue, letting other processes use the CPU.

In this project, the multilevel feedback queue algorithm consists of 3 queues:
  - First queue: RoundRobin with quantum = 8 and size = 10
  - Second queue: RoundRobin with quantum = 16 and size = 20
  - Third queue: First Come First Serve (FCFS) with size = 30
We have 100 process and each process is assigned a random burst time.
The CPU devides its time by giving the first queue 50% of its time, the second queue 30% of its time and the third queue 20% of its time.
Process promotion and demotion:
  - The process is promoted from the first queue to the second queue if it was not complete in a quantum of 8.
  - In the second queue, there is a 50% chance that the process is demoted back to the first queue and a 50% chance it is promoted to the third queue if it was not processed completely after a quantum of 16. 

II. CHALLENGES FACED:
dividing the cpu time was the challenging part in this project. I used the time.h library to aid in implementing that. 

III. HOW TO RUN:
Running this code is very simple just compile the main.c file and run. it does not take any user input so you should be good to go!



