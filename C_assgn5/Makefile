CC=gcc
CFLAGS= -std=c11 -Wall -Werror -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wuninitialized -Wno-return-local-addr -Wunused -Wextra -g3 -O0 -pthread

all: compute

compute: compute.c
	$(CC) $(CFLAGS) -o compute compute.c

clean:
	rm -rf compute
