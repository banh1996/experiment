// THIS FILE MAY NOT BE MODIFIED

#ifndef STORAGE_ENGINE_H
#define STORAGE_ENGINE_H

#define BLOCK_SIZE 512
#define NUM_BLOCKS 16384
#define CACHE_SIZE 64

// defined in storage-engine.c
int open_storage(char* filename);
int read_storage(int key, char* block);
int write_storage(int key, char* block);
int close_storage();

// defined in client.c
int read_block(int fd, int key, char* block);
int write_blocks(int fd, int start_key, char* block, int num_blocks);

#endif // STORAGE_ENGINE
