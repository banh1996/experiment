CC=gcc
CFLAGS= -std=gnu99 -Wall -Wno-return-local-addr -Wuninitialized -Wunused -Wextra -g

all: bai5.o
	$(CC) $(CFLAGS) -o test bai5.o

# device-controller-simulator.o: device-controller-simulator.c device-controller.h
# 	$(CC) $(CFLAGS) -c device-controller-simulator.c

bai5.o: bai5.c
	$(CC) $(CFLAGS) -c bai5.c

clean:
	rm -rf *.o
	rm -rf test
