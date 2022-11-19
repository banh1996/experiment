CC=g++
CFLAGS= -std=c++11 -O2 -Wall

all: hw1.o hw2.o
	@echo "Build all done"

hw1.o: hw1.cpp
	$(CC) $(CFLAGS) -o $@ hw1.cpp

hw2.o: hw2.cpp
	$(CC) $(CFLAGS) -o $@ hw2.cpp

clean:
	rm -rf *.o
	rm -rf valgrind-out.txt
