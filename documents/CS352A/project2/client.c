#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>
#include <pthread.h>
#include <semaphore.h>
#include "storage-engine.h"

pthread_t test_thread1;
pthread_t test_thread2;

int read_block(int fd, int key, char* block) {
    lseek(fd, key * BLOCK_SIZE, SEEK_SET);
    if (read(fd, block, BLOCK_SIZE) != BLOCK_SIZE) {
        return -1;
    }
    return 0;
}

int write_blocks(int fd, int start_key, char* block, int num_blocks) {
    printf("entering write_blocks for start key %d\n", start_key);
    // write is modified to take a long time, will two threads write to the
    // same key at the same time?
    sleep(1);
    lseek(fd, start_key * BLOCK_SIZE, SEEK_SET);
    if (write(fd, block, BLOCK_SIZE*num_blocks) != BLOCK_SIZE*num_blocks) {
        return -1;
    }
    printf("exiting write_blocks\n");
    return 0;
}

/**
 * Example test thread.
 **/
void* run_test_thread1(void* arg) {
    char buff[BLOCK_SIZE];
    buff[0] = 'a';
    buff[1] = '\0';

    write_storage(10, buff);
    read_storage(10, buff);
}

/**
 * Example test thread.
 **/
void* run_test_thread2(void* arg) {
    char buff[BLOCK_SIZE];
    buff[0] = 'b';
    buff[1] = '\0';

    write_storage(10, buff);
    read_storage(10, buff);
}

/**
 * Example test.
 **/
void test(char* filename) {
    open_storage(filename);

    pthread_create(&test_thread1, NULL, run_test_thread1, NULL);
    pthread_create(&test_thread2, NULL, run_test_thread2, NULL);

    pthread_join(test_thread1, NULL);
    pthread_join(test_thread2, NULL);
    
    close_storage(filename);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: client store_filename\n");
        exit(1);
    }

    test(argv[1]);

    return 0;
}

