CC = g++ -std=c++11 -O2 -g -Wno-deprecated -Wno-write-strings 

all: ssp

ssp: Fibonacci.o  dijkstra.o ssp.o
	$(CC) -o ssp Fibonacci.o  dijkstra.o ssp.o

ssp.o: ssp.cpp
	$(CC) -c ssp.cpp

dijkstra.o: dijkstra.cpp
	$(CC) -c dijkstra.cpp

Fibonacci.o: Fibonacci.cpp
	$(CC) -c Fibonacci.cpp

clean:
	rm -f ssp
	rm -f *.o
    