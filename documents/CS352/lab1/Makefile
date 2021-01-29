CC=gcc
CFLAGS= -std=gnu99 -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -Wno-return-local-addr -Wuninitialized -Wunused -Wextra -g

all: device-controller-simulator.o echo-driver.o
	$(CC) $(CFLAGS) -o main device-controller-simulator.o echo-driver.o

device-controller-simulator.o: device-controller-simulator.c device-controller.h
	$(CC) $(CFLAGS) -c device-controller-simulator.c

echo-driver.o: echo-driver.c
	$(CC) $(CFLAGS) -c echo-driver.c

clean:
	rm -rf *.o
	rm -rf main
