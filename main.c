#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include "priorityQueue.h"

#define BUFFER_SIZE 100
#define MAX_PROCESS_STRING 8
#define READY_STATE 1
#define RUNNING_STATE 2
#define TERMINATED_STATE 3


/* The process struct */
struct Process {
    int time_arrived;
    char name[MAX_PROCESS_STRING];
    int service_time;
    int memory_size;
    int remainingTime; // remaining time after execution
    int state; // process state (READY=1, RUNNING=2, TERMINATED=3)
};

struct Process *readProcesses(const char* filename, int* numProcesses);
int compareSimTime(struct Process *p, int simTime, int cycle, int quantum, int *processCount);
int calcSimTime(int cycle, int quantum);

int main(int argc, char *argv[]) {

    /* Reading the input file and enqueue the processes into the priority queue */
    char *filename = NULL;
    char *scheduler = NULL;
    char *memoryStrat = NULL;
    int quantum;

    int c;
    /* Parse command line arguments */
    while ((c = getopt(argc, argv, ":f:s:m:q")) != -1) {
        switch (c) {
            case 'f':
                filename = optarg;
                break;
            case 's':
                // scheduler {SJF, RR}
                scheduler = optarg;
                break;
            case 'm':
                // memory-strategy {infinite, best-fit}
                memoryStrat = optarg;
                break;
            case 'q':
                // quantum {1, 2, 3}
                quantum = atoi(optarg);
                break;
            case '?':
                if (optopt == 'f') {
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                } else if (isprint(optopt)) {
                    fprintf(stderr, "Unrecognized option `-%c'.\n", optopt);
                } else {
                    fprintf(stderr, "Unrecognized option character `\\x%x'.\n", optopt);
                }
                return 1;
            default:
                exit(EXIT_FAILURE);
        }
    }

    if (filename == NULL) {
        fprintf(stderr, "Usage: %s -f filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int numProcesses;
    struct Process *processes = readProcesses(filename, &numProcesses);
    struct PriorityQueue *inputQueue = init_queue();

    int processCount = 0;
    int simTime = 0;
    int cycle = 0;
    for (int i=0; i<numProcesses; i++) {
        if (compareSimTime(processes + i, simTime, cycle, quantum, &processCount)) {
            enqueue(inputQueue, processes + i, i);
            (processes+i)->state = READY_STATE;
        }

    }

    struct PriorityQueue *readyQueue = init_queue();
    struct Node *curr = inputQueue->head;
    for (int i=0; i<processCount; i++) {
        if (curr->process_node->state == READY_STATE) {
            enqueue(readyQueue, (curr->process_node) + i, i);
        }
    }

    printQueue(inputQueue);

    free(processes);
    freePQ(inputQueue);

    return 0;
}


/* Reads the contents of a text file and its number of processes
 * returns a dynamically allocated array of Process structures */
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
    
    /* repositions the file pointer associated with stream to the beginning of the file */
    /* Read the file again and parse the buffer line */
    rewind(file);
    int i = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        sscanf(buffer, "%d %s %d %d", &processes[i].time_arrived, processes[i].name, &processes[i].service_time, &processes[i].memory_size);
        i++;
    }

    fclose(file);

    return processes;
}


/* Calculates the current simulation time */
int calcSimTime(int cycle, int quantum) {
    return cycle * quantum;
}


/* To check if the process' arrivedTime is smaller than current simulation time */
int compareSimTime(struct Process *p, int simTime, int cycle, int quantum, int *processCount) {

    if (p->time_arrived < simTime) {
        (*processCount)++;
        return 1;
    }

    return 0;
}

