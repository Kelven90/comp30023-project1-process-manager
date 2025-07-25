#include "priorityQueue.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_PROCESS_STRING 8

/* The process struct */
struct Process {
    int time_arrived;
    char name[MAX_PROCESS_STRING];
    int service_time;
    int memory_size;
    int remainingTime; // remaining time after execution
    int state; // process state (READY=0, RUNNING=1, TERMINATED=2)
};

/* The node struct for the priority queue */
struct Node {
    struct Process *process_node;
    int priority;
    struct Node *next;
};

struct PriorityQueue {
    struct Node *head;
    struct Node *tail;
    int size;
};

/* Create a new node */
struct Node *create_NewNode(struct Process *p, int prior) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->process_node = p;
    newNode->priority = prior;
    newNode->next = NULL;

    return newNode;
}


/* Initialise a new priority queue */
struct PriorityQueue *init_queue() {
    struct PriorityQueue *newQueue = (struct PriorityQueue *)malloc(sizeof(struct PriorityQueue));
    assert(newQueue);
    newQueue->head = NULL;
    newQueue->tail = NULL;
    newQueue->size = 0;

    return newQueue;
}

/* Check if the queue is empty */
int is_emptyQueue(struct PriorityQueue *pq) {
    return (pq->head == NULL && pq->size == 0);
}

/* To enqueue a process_node into the priority queue based on its priority */
void enqueue(struct PriorityQueue *pq, struct Process *p, int prior) {
    struct Node *newNode = create_NewNode(p, prior);

    /* This is the first insertion to the queue */
    if (is_emptyQueue(pq)) {
        pq->head = newNode;
        pq->tail = newNode;
    /* If the insertion has higher priority than the head node, place it as the first for the queue */
    } else if (prior < pq->head->priority) {
        newNode->next = pq->head;
        pq->head = newNode;
    } else {
        struct Node *prevNode = pq->head;
        struct Node *currNode = pq->head->next;
        /* Traverse through the priority queue for insertion based on priority*/
        while (currNode != NULL && prior > currNode->priority) {
            prevNode = currNode;
            currNode = currNode->next;
        }
        newNode->next = prevNode->next;
        prevNode->next = newNode;

        if (currNode == NULL) {
            pq->tail = newNode;
        }
    }
    pq->size++;

}

/* Return the first process in the front of the queue */
struct Process *dequeue(struct PriorityQueue *pq) {
    if (is_emptyQueue(pq)) {
        return NULL;
    } 

    struct Process *p = pq->head->process_node;
    struct Node *temp = pq->head;
    free(temp);
    pq->size--;

    /* Dequeuing the last process in the queue, set the tail node to NULL */
    if (is_emptyQueue(pq)) {
        pq->tail = NULL;
    }

    return p;
}

void printQueue(struct PriorityQueue *pq) {
    if (is_emptyQueue(pq)) {
        printf("Queue is empty\n");
        return ;
    }

    struct Node *curr = pq->head;

    while (curr != NULL) {
        printf("Arrived Time: %d, Process Name: %s, Required Time: %d, Memory Size: %d, Priority: %d\n",
            curr->process_node->time_arrived, curr->process_node->name, curr->process_node->time_arrived, 
            curr->process_node->memory_size, curr->priority);
        curr = curr->next;
    }
}


void freePQ(struct PriorityQueue *pq){
    struct Node *curr = pq->head;

    if (!pq) {
        return;
    }

    while (curr != NULL) {
        curr = curr->next;
        free(curr);
    }
    free(pq);

}