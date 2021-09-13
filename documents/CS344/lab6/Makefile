CC=gcc
CFLAGS= -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -Wno-return-local-addr -Wuninitialized -Wunused -Wextra -g

all:
	$(CC) $(CFLAGS) -o BennySh parse_example.c cmd_parse.c

BennySh:
	$(CC) $(CFLAGS) -o BennySh parse_example.c cmd_parse.c

BennySh.o:
	$(CC) $(CFLAGS) -o BennySh parse_example.c cmd_parse.c

clean:
	rm -rf BennySh
	rm -rf valgrind-out.txt
