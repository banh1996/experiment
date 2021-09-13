CC=gcc
CFLAGS= -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -Wuninitialized -Wno-return-local-addr -Wunused -Wextra -pthread -g

all:
	$(CC) $(CFLAGS) -o main.o main.c

main.o:
	$(CC) $(CFLAGS) -o main.o main.c

clean:
	rm -rf main.o
	rm -rf valgrind-out.txt
