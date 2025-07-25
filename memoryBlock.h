/* Visible structs and functions for memory block */
#define MEM_SIZE 2048
#define MAX_PROCESS_STRING 8

struct Block {
    int baseAddress; //starting address of memory block
    int endAddress; //ending address of memory block
    char processName[MAX_PROCESS_STRING]; //process that owns the memory block
};

struct Memory {
    int size;
    Block blocks[MEM_SIZE];
};

struct Memory *init_memBlock();
int bestFitMem(Memory *memory, int memorySize);
int allocateMem(Memory *memory, char *pName, int memorySize);
// void destroy_memory(Memory *memory);
void freeMem(Memory *memory, char *pName);