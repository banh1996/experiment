CC=gcc
CFLAGS= -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -Wno-return-local-addr -Wuninitialized -Wunused -Wextra -pthread -g

all:
	$(CC) $(CFLAGS) -o primeMT.o primeMT.c

primeMT:
	$(CC) $(CFLAGS) -o primeMT.o primeMT.c
	./testPrimes.bash

primeMT.o:
	$(CC) $(CFLAGS) -o primeMT.o primeMT.c

clean:
	rm -rf primeMT.o
	rm -rf valgrind-out.txt
