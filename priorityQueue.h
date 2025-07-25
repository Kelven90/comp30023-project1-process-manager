/* Visible structs and functions for priority queues */

/* The priority queue struct */
struct Process;

struct Node;

struct PriorityQueue;

/* Create a new node */
struct Node *create_NewNode(struct Process *p, int prior);

/* Initialise a new priority queue */
struct PriorityQueue *init_queue();

/* Check if the queue is empty */
int is_emptyQueue(struct PriorityQueue *pq);

/* To enqueue a process_node into the priority queue based on its priority */
void enqueue(struct PriorityQueue *pq, struct Process *p, int priority);

/* Return the first process in the front of the queue */
struct Process *dequeue(struct PriorityQueue *pq);

/* Print out the content of the priority queue */
void printQueue(struct PriorityQueue *pq);

/* Remove all items from priority queue and free the queue. */
void freePQ(struct PriorityQueue *pq);