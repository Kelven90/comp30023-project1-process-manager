/* Implementations for helper functions to do with process manager tasks */

#include <stdio.h>
#include <stdlib.h>

#include "priorityQueue.h"

#define BUFFER_SIZE 100

struct Process *readProcesses(const char *filename, int *numProcesses) {

    /* Open the input text file */
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Failed to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    *numProcesses = 0;
    /* Count the number of processes for the input file 
     * by counting the number of lines */
    while (fgets(buffer, sizeof(buffer), file)) {
        (*numProcesses)++;
    }

    struct Process *processes = malloc((*numProcesses) * sizeof(struct Process));
    if (!processes) {
        printf("Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }
    
    /* Repositions the file pointer associated with stream to the beginning of the file */
    /* Read the file again and parse the buffer line */
    rewind(file);
    int i = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        sscanf(buffer, "%d %s %d %d", &processes[i].time_arrived, processes[i].name, &processes[i].service_time, &processes[i].memory_size);
        strcpy(processes[i].state, "INITIAL");
        processes[i].remaining_serviceTime = processes[i].service_time;
        processes[i].turnaround_time = 0;
        processes[i].overhead_time = 0;
        processes[i].assignedAddress = -1;
        i++;
    }

    fclose(file);

    return processes;
}


int compareSimTime(struct Process *p, int simTime, int cycle, int quantum, int *processCount) {

    if (p->time_arrived <= simTime) {
        (*processCount)++;
        return 1;
    }

    return 0;
}


struct Process *SJF(struct PriorityQueue *readyQueue) {

    if (is_emptyQueue(readyQueue)) {
        return NULL;

    } else {
        sortQueueByServiceTime(readyQueue);
        struct Process *shortestProcess = dequeue(readyQueue);
        strcpy(shortestProcess->state, "RUNNING");

        return shortestProcess;
    }
}


void sortQueueByServiceTime(struct PriorityQueue *pq) {
    int n = pq->size;

    if (n != 0) {
        struct Process *processes = pq->head->process_node;
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (processes[j].service_time < processes[i].service_time ||
                    (processes[j].service_time == processes[i].service_time &&
                    processes[j].time_arrived < processes[i].time_arrived) ||
                    (processes[j].service_time == processes[i].service_time &&
                    processes[j].time_arrived == processes[i].time_arrived &&
                    strcmp(processes[j].name, processes[i].name) < 0)) {
                    struct Process temp = processes[i];
                    processes[i] = processes[j];
                    processes[j] = temp;
                }
            }
        }
    }
}

void printPerformanceStatistics(struct Process *p, int simTime, int numProcesses, int quantum) {

    double totalTurnaroundTime = 0;
    double totalOverheadTime = 0;

    for (int i = 0; i < numProcesses; i++) {
        if (strcmp(p[i].state, "FINISHED") == 0) {
            // totalTurnaroundTime += p[i].turnaround_time + quantum - 1;
            totalTurnaroundTime += p[i].turnaround_time;
            totalOverheadTime += p[i].overhead_time;
        }
    }
    /* To find the maximum time overhead among the processes */
    double maxOverhead = -1;
    for (int i = 0; i < numProcesses; i++) {
        if (p[i].overhead_time > maxOverhead) {
            maxOverhead = p[i].overhead_time;
        }
    }

    /* Print the Performance Statistics */
    double avgTurnaroundTime = ceil(totalTurnaroundTime / numProcesses);
    double avgOverheadTime = totalOverheadTime / numProcesses;
    printf("Turnaround time %d\n", (int)avgTurnaroundTime);
    printf("Time overhead %.2f %.2f\n", maxOverhead, avgOverheadTime);
    printf("Makespan %d\n", simTime);

}