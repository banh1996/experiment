#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
#include "storage-engine.h"

/**
 * File descriptor of the storage file.
 **/
int fd = -1;

/**
 * Opens the storage file.
 * Returns 0 if successful, -1 if not.
 **/
int open_storage(char* filename) {
    // open or create the storage file
    if ((fd = open(filename, O_RDWR | O_CREAT | O_SYNC)) == -1) {
        return -1;
    }

    // increase the size of the file if it is not learge enough
    int file_size = lseek(fd, 0L, SEEK_END);
    if (file_size < BLOCK_SIZE * NUM_BLOCKS) {
        lseek(fd, BLOCK_SIZE * NUM_BLOCKS - 1, SEEK_SET);
        write(fd, "\0", 1);
    }

    return 0;
}

/**
 * Reads one block of data from storage at the block index indicated by key.
 * On return the array pointed to by block contains the data.
 * Returns 0 if successful, -1 if not.
 **/
int read_storage(int key, char* block) {
    return read_block(fd, key, block);
}

/**
 * Writes one block of data to storage at the block index indicated by key.
 * Returns 0 if successful, -1 if not.
 **/
int write_storage(int key, char* block) {
     return write_blocks(fd, key, block, 1);
}

/**
 * Closes the storage file.
 **/
int close_storage() {
    return close(fd);
}
