CC=gcc
CFLAGS= -std=gnu99 -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -Wno-return-local-addr -Wuninitialized -Wunused -Wextra -g

all:
	$(CC) $(CFLAGS) -o mystat mystat.c
	$(CC) $(CFLAGS) -o csv2bin csv2bin.c
	$(CC) $(CFLAGS) -o bin2csv bin2csv.c

mystat.o:
	$(CC) $(CFLAGS) mystat.c -o mystat.o

mystat: mystat.o
	$(CC) $(CFLAGS) mystat.c -o mystat.o

csv2bin.o:
	$(CC) $(CFLAGS) -o csv2bin.o csv2bin.c

csv2bin: csv2bin.o
	$(CC) $(CFLAGS) -o csv2bin.o csv2bin.c

bin2csv.o:
	$(CC) $(CFLAGS) -o bin2csv.o bin2csv.c

bin2csv: bin2csv.o
	$(CC) $(CFLAGS) -o bin2csv.o bin2csv.c

clean:
	rm -rf mystat.o
	rm -rf csv2bin.o
	rm -rf bin2csv.o
