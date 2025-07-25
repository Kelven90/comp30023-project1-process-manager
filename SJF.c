#include "priorityQueue.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*A process is
considered to have been submitted to the system if its arrival time is less than or equal to
the current simulation time T

Sim_Time = num_cycle * quantum (T=NxQ)

Shortest Job First (SJF): The process with the shortest service time should be chosen among
all the READY processes to run

If there is a
tie when choosing the shortest process (i.e. two or more processes have the same service time),
choose the process which has the earlier arrival time. If there are two or more processes that have
the same service time as well as the same arrival time, select the process whose name comes first
lexicographically.

*/

struct PriorityQueue *SFJScheduling(Struct PriorityQueue *readyQueue) {
    
}


