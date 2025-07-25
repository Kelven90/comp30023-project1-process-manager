/* Visible helper functions to do with process manager tasks */

#include "priorityQueue.h"

/* Reads the contents of a text file and its number of processes
 * returns a dynamically allocated array of Process structures */
struct Process *readProcesses(const char* filename, int* numProcesses);

/* To check if the process' arrivedTime is smaller than/equal to current simulation time */
int compareSimTime(struct Process *p, int simTime, int cycle, int quantum, int *processCount);

/* Implement the Shortest Job First (SJF) scheduling
Return the process with shortest service time in the queue */
struct Process *SJF(struct PriorityQueue *readyQueue);

/* Sort the queue in ascending order and allow tie-breakers
(earlier arrival time, name comes first lexicographically) */
void sortQueueByServiceTime(struct PriorityQueue *pq);

/* Calculates the Performance Statistics (Turnaround Time, Time overhead, Makespan)
   for the processes and print the results */
void printPerformanceStatistics(struct Process *p, int simTime, int numProcesses, int quantum);