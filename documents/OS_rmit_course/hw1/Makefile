CC=gcc
CFLAGS= -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -Wno-return-local-addr -Wuninitialized -Wunused -Wextra -g

all: task2 Task1filter task3 task4
	@echo "Build all done"

Task1filter: task1.c common_def.h
	$(CC) $(CFLAGS) -o $@ task1.c

task2: task2.c common_def.h
	$(CC) $(CFLAGS) -o $@ task2.c

task3: task3.c common_def.h
	$(CC) $(CFLAGS) -o $@ task3.c -lpthread

task4: task4.c common_def.h
	$(CC) $(CFLAGS) -o $@ task4.c -lpthread

clean:
	rm -rf Task1filter task2 task3 task4 task5
	rm -rf myfifo*
	rm -rf wordfile*
	rm -rf valgrind-out.txt
