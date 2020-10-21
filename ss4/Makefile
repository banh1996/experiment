CC=gcc
CFLAGS= -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -Wuninitialized -Wno-return-local-addr -Wunused -Wextra -pthread -g

all:
	$(CC) $(CFLAGS) -o primesMT primesMT.c

primesMT:
	$(CC) $(CFLAGS) -o primesMT primesMT.c

primesMT.o:
	$(CC) $(CFLAGS) -o primesMT primesMT.c

clean:
	rm -rf primesMT
	rm -rf valgrind-out.txt
