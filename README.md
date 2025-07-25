# COMP30023 Project 1: Process Manager (University of Melbourne)

This repository contains my implementation of a simulated process manager, developed as part of **COMP30023: Computer Systems (Semester 1, 2023)** at the University of Melbourne.

## Project Overview

This project simulates:
- **Shortest Job First (SJF)** and **Round Robin (RR)** CPU scheduling.
- **Best-Fit** and **infinite** memory allocation strategies.
- Process lifecycle transitions (READY → RUNNING → FINISHED).
- Optional control of real subprocesses using `fork`, `exec`, signals, and pipes.

The simulation models a CPU environment where processes arrive, are scheduled for execution, and consume simulated memory. The system outputs execution logs and performance statistics.

## Features Implemented

- Shortest Job First (non-preemptive)
- Round Robin (preemptive, quantum-based)
- Best-fit memory allocation
- Infinite memory mode
- Full process lifecycle tracking
- Execution transcript logging to stdout
- Performance statistics calculation:
  - Turnaround time
  - Time overhead (avg & max)
  - Makespan
- Clean Makefile build system (`make` and `make clean`)
- Warning-free compilation with `-Wall`

## Build & Run

To compile the program:

```bash
make clean && make
````

To run the simulation:

```bash
./allocate -f sample_input/processes.txt -s RR -m best-fit -q 3
```

### Command-Line Arguments

```
-f <filename>           Path to process input file
-s <SJF | RR>           Scheduling algorithm
-m <infinite | best-fit> Memory allocation strategy
-q <1 | 2 | 3>          Quantum length in seconds
```

## Sample Input Format

Each line in the process file is formatted as:

```
<arrival_time> <process_name> <service_time> <memory_requirement>
```

Example:

```
0 P1 20 32
5 P2 30 128
29 P3 10 64
```

## Sample Output (Execution Transcript)

```
0,READY,process_name=P1,assigned_at=0
0,RUNNING,process_name=P1,remaining_time=20
20,FINISHED,process_name=P1,proc_remaining=2
...
```

## Sample Output (Performance Stats)

```
Turnaround time 32
Time overhead 1.08 1.04
Makespan 120
```

## Assignment Details
Refer to the assignment_spec/ folder in this repository for the original project specification PDFs.

## License

This project is released under the [MIT License](LICENSE).

## Academic Honesty Notice

This repository contains code written as part of a university assignment. It is intended **only for educational and portfolio purposes**. If you are currently enrolled in COMP30023 or a similar course, **do not reuse this code** without proper authorization to avoid academic misconduct.
