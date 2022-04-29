CFLAGS=-lpthread -lncurses
FILES=locksync elevator.log hw7

locksync: locksync.c main.c elevator.h
	gcc $^ -o $@ $(CFLAGS)

hw7: hw7.c main.c elevator.h
	gcc $^ -o $@ $(CFLAGS)

clean:
	rm -f $(FILES) *.o
