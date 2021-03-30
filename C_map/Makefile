CC=g++
CFLAGS= -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wuninitialized -Wno-return-local-addr -Wunused -Wextra

all: proj5.o

proj5.o: treasuremap.o proj5.cpp
	$(CC) $(CFLAGS) -o proj5.o proj5.cpp treasuremap.o

treasuremap.o: treasuremap.cpp treasuremap.h
	$(CC) $(CFLAGS) -c treasuremap.cpp

clean:
	rm -rf *.o
