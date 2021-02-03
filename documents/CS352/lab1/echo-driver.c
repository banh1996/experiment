#include <stdlib.h>
#include <stdio.h>
#include "device-controller.h"

typedef struct buffer_t {
	char *data;
	int size;
	int head;
	int tail;
} buffer_t;

buffer_t g_buf;
char g_is_done_interrupt = 1;

int is_full() {
	/* TODO */
	return ((g_buf.tail-g_buf.head+1)%g_buf.size == 0)?1:0;
}

int is_empty() {
	/* TODO */
	return (!is_full() && g_buf.head == g_buf.tail)?1:0;
}

void enqueue(int val) {
	/* TODO */
	if (!is_full()) {
		*(g_buf.data+g_buf.tail) = (char)val;
		g_buf.tail = (g_buf.tail+1)%g_buf.size;
	}
}

int dequeue() {
	/* TODO */
	if (!is_empty()) {
		g_buf.head = (g_buf.head+1)%g_buf.size;
		return 1;
	}
	return 0;
}

void read_interrupt(int c) {
	/* TODO */
	enqueue(c);
	if (g_is_done_interrupt) {
		write_device(g_buf.data[g_buf.head]);
		g_is_done_interrupt = 0;
	}
}

void write_done_interrupt() {
	/* TODO */
	dequeue();
	g_is_done_interrupt = 1;
}

int main(int argc, char* argv[]) {
	/* TODO */
	if (argc < 2) {
		printf("argument must be at less 1\n");
		return 1;
	}
	g_buf.size = atoi(argv[1]);
	g_buf.data = malloc(sizeof(char*)*g_buf.size);
	start();
	free(g_buf.data);
	return 0;
}
