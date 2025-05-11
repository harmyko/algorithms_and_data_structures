all: flight_router.exe

flight_router.exe: main.o flight_graph.o
	gcc -std=c99 -Wall -o flight_router.exe main.o flight_graph.o

main.o: main.c flight_graph.h
	gcc -std=c99 -Wall -c main.c

flight_graph.o: flight_graph.c flight_graph.h
	gcc -std=c99 -Wall -c flight_graph.c

test: all
	./airport_sim.exe -test