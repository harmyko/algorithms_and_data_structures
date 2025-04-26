all: airport_sim.exe

airport_sim.exe: main.o priorityQueue.o airport_sim.o BigInteger.o
	gcc -std=c99 -Wall -o airport_sim.exe main.o priorityQueue.o airport_sim.o BigInteger.o

main.o: main.c airport_sim.h
	gcc -std=c99 -Wall -c main.c

priorityQueue.o: priorityQueue.c priorityQueue.h
	gcc -std=c99 -Wall -c priorityQueue.c

airport_sim.o: airport_sim.c airport_sim.h priorityQueue.h BigInteger.h
	gcc -std=c99 -Wall -c airport_sim.c

BigInteger.o: BigInteger.c BigInteger.h
	gcc -std=c99 -Wall -c BigInteger.c

test: all
	./airport_sim.exe -test