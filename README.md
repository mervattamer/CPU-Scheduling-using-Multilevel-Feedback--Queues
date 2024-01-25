# CPU Scheduling Using Queues

## Project Description

This project is a C source code implementation of the Multi-level Feedback Queue scheduling algorithm. The Multilevel feedback queue algorithm categorizes processes into separate queues based on their CPU needs, promotes/demotes processes between queues, gives attention to processes using the CPU quickly, and prioritizes processes with frequent input/output (I/O) operations.

### Algorithm Overview:

1. Puts different processes into separate queues based on CPU needs.
2. Promotes/demotes a process to different queues.
3. Gives more attention to processes that use the CPU quickly.
4. Gives priority to processes that perform a lot of input/output (I/O) operations.

### Project Implementation:

The multilevel feedback queue algorithm in this project consists of 3 queues:

- **First Queue:** RoundRobin with quantum = 8 and size = 10
- **Second Queue:** RoundRobin with quantum = 16 and size = 20
- **Third Queue:** First Come First Serve (FCFS) with size = 30

There are 100 processes, each assigned a random burst time. The CPU allocates its time as follows:
- First queue: 50%
- Second queue: 30%
- Third queue: 20%

**Process Promotion and Demotion:**
- Promotion from the first queue to the second queue if not completed in a quantum of 8.
- In the second queue, there is a 50% chance of demotion back to the first queue and a 50% chance of promotion to the third queue if not completed after a quantum of 16.

## Challenges Faced

The main challenge in this project was dividing the CPU time appropriately. The time.h library was utilized to aid in the implementation.

## How to Run

To run the code, follow these steps:

1. Compile the `main.c` file.
    ```bash
    gcc main.c -o scheduler
    ```

2. Run the executable.
    ```bash
    ./scheduler
    ```

The program does not require any user input and should execute smoothly.

---

Feel free to customize this template based on any additional information or details specific to your project.
