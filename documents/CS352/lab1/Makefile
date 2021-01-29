CC=gcc
CFLAGS= -std=gnu99 -Wall -Wno-return-local-addr -Wuninitialized -Wunused -Wextra -g

all: device-controller-simulator.o echo-driver.o
	$(CC) $(CFLAGS) -o echo-driver device-controller-simulator.o echo-driver.o

device-controller-simulator.o: device-controller-simulator.c device-controller.h
	$(CC) $(CFLAGS) -c device-controller-simulator.c

echo-driver.o: echo-driver.c
	$(CC) $(CFLAGS) -c echo-driver.c

clean:
	rm -rf *.o
	rm -rf echo-driver
