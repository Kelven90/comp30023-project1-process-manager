#include "memoryBlock.h"

/* Initialize the memory block */
struct MemoryBlock *init_memBlock() {
    Memory *memory = (Memory *)malloc(sizeof(Memory));
    memory->size = 0;

    return memory;
}

/* Search for the smallest available memory block for the process */
int bestFitMem(Memory *memory, int memorySize) {
    int index = -1;
    int bestfitSize = MEM_SIZE;

    for (int i = 0; i < memory->size; i++) {
        int blockSize = memory->blocks[i].endAddress - memory->blocks[i].baseAddress;
        if (blockSize >= memorySize && blockSize < bestfitSize) {
            index = i;
            bestfitSize = blockSize;
        }
    }
    return index;
}

/* Allocate memory to process using best Fit algorithm */
int allocateMem(Memory *memory, char *pName, int memorySize) {
    int bestFitIndex = bestFitMem(memory, memorySize);

    /* Failed to allocate memory */
    if (bestFitIndex == -1) {
        return -1; 
    }

    Block *bestFitBlock = &memory->blocks[bestFitIndex];
    int baseAddr = bestFitBlock->baseAddress;

    /* Allocate the memory block with the process required memory size and name */
    bestFitBlock->baseAddr += memorySize;
    strcpy(bestFitBlock->processName, pName);

    /* Add a new block for the remaining memory */
    Block *remainingBlock = &memory->blocks[memory->size];
    remainingBlock->baseAddress = bestFitBlock->baseAddress;
    remainingBlock->endAddress = bestFitBlock->endAddress;
    strcpy(remainingBlock->processName, "");

    memory->size++;

    return base_address;
}


void freeMem(Memory *memory, char *pName) {

    for (int i = 0; i < memory->size; i++) {
        Block *block = &memory->blocks[i];
        if (strcmp(block->processName, pName) == 0) {
            /* Free the memory block that is used by the process */
            block->processName[0] = NULL;

            /* Merge adjacent block */
            if (i < memory->size - 1) {
                Block *nextBlock = &memory->blocks[i+1];
                if (strcmp(nextBlock->processName, "") == 0) {
                    block->endAddress = nextBlock->endAddress;
                    memory->size--;
                    for (int j = i+1; j < memory->size; j++) {
                        memory->blocks[j] = memory->blocks[j+1];
                    }
                }
            }

            if (i > 0) {
                Block *prevBlock = &memory->blocks[i-1];
                if (strcmp(prevBlock->processName, "") == 0) {
                    prevBlock->endAddress = block->endAddress;
                    memory->size--;
                    for (int j = i; j < memory->size; j++) {
                        memory->blocks[j] = memory->blocks[j+1];
                    }
                }
            }

            break;
        }
    }
}

