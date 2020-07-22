CC=gcc
CFLAGS= -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -Wno-return-local-addr -Wuninitialized -Wunused -Wextra -g

all:
	$(CC) $(CFLAGS) -o reclookup reclookup.c
	$(CC) $(CFLAGS) -o bigFiles bigFiles.c
	$(CC) $(CFLAGS) -o BennySh parse_example.c cmd_parse.c

reclookup:
	$(CC) $(CFLAGS) -o reclookup reclookup.c

bigFiles:
	$(CC) $(CFLAGS) -o bigFiles bigFiles.c

BennySh:
	$(CC) $(CFLAGS) -o BennySh parse_example.c cmd_parse.c

reclookup.o:
	$(CC) $(CFLAGS) -o reclookup reclookup.c

bigFiles.o:
	$(CC) $(CFLAGS) -o bigFiles bigFiles.c

BennySh.o:
	$(CC) $(CFLAGS) -o BennySh parse_example.c cmd_parse.c

clean:
	rm -rf reclookup
	rm -rf bigFiles
	rm -rf BennySh
	rm -rf valgrind-out.txt
