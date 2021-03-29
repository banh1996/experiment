CC=gcc
CFLAGS= -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wmissing-prototypes -Wuninitialized -Wno-return-local-addr -Wunused -Wextra -pthread -g

all: pong

pong: pong.c
	$(CC) $(CFLAGS) -o pong.o pong.c -lncurses

clean:
	rm -rf pong.o
