CC = g++ -std=c++0x -O2 -g -Wno-deprecated -Wno-write-strings 

all: ssp routing

routing: Fibonacci.o  dijkstra.o BinaryTrie.o routing.o
	$(CC) -o routing Fibonacci.o  dijkstra.o BinaryTrie.o routing.o

ssp: Fibonacci.o  dijkstra.o ssp.o
	$(CC) -o ssp Fibonacci.o  dijkstra.o ssp.o

routing.o: routing.cpp
	$(CC) -c routing.cpp

ssp.o: ssp.cpp
	$(CC) -c ssp.cpp

BinaryTrie.o: BinaryTrie.cpp
	$(CC) -c BinaryTrie.cpp

dijkstra.o: dijkstra.cpp
	$(CC) -c dijkstra.cpp

Fibonacci.o: Fibonacci.cpp
	$(CC) -c Fibonacci.cpp

clean:
	rm -f ssp
	rm -f routing
	rm -f *.o
    