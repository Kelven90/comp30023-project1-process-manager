# COMP30023 Project 1: Process Manager (University of Melbourne)

This repository contains my implementation of a simulated process manager, developed as part of **COMP30023: Computer Systems (Semester 1, 2023)** at the University of Melbourne.

## Project Overview

This project simulates a simplified operating system process manager entirely in C. It models how a CPU schedules multiple processes and how memory is allocated to them in a controlled environment. Key functionalities include:

- **Process scheduling** using two classic algorithms:
  - **Shortest Job First (SJF):** Non-preemptive — each process runs until completion.
  - **Round Robin (RR):** Preemptive — processes take turns in fixed time slices (quantums).
  
- **Memory allocation** with two modes:
  - **Infinite memory mode:** Assumes unlimited memory; processes are always admitted.
  - **Best-Fit allocation:** Simulates realistic memory constraints and fragmentation. Processes must fit into the smallest available memory block.

- **Lifecycle simulation** of each process through the states: `NEW → READY → RUNNING → FINISHED`.

- **Timing and performance tracking**, including:
  - When processes start, stop, and complete.
  - Time statistics such as turnaround time, time overhead, and makespan.

- **Text-based logging output** formatted to mimic a real OS scheduler's execution trace.

Optional support for launching and managing real subprocesses (disabled by default in this repo).

This implementation includes all supporting data structures and logic such as process queues, memory maps, scheduling decisions, and real-time simulation updates without relying on any external libraries.

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
