MAKEFLAGS += -B

all: allocate

allocate: main.o priorityQueue.o
	gcc -Wall -o allocate -g -lm main.o priorityQueue.o

main.o: main.c priorityQueue.h
	gcc -c main.c -Wall -g

priorityQueue.o: priorityQueue.c priorityQueue.h
	gcc -c priorityQueue.c -Wall -g

clean:
    rm -f *.o allocate
