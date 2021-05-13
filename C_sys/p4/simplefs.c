#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "simplefs.h"

#define ROOT_BLOCK_START 5
#define MAX_FILENAME_BYTE 110
// Global Variables =======================================
int vdisk_fd; // Global virtual disk file descriptor. Global within the library.
              // Will be assigned with the vsfs_mount call.
              // Any function in this file can use this.
              // Applications will not use  this directly. 

#define NOTHING_MODE 0
#define APPENDING_MODE 1
#define READING_MODE 2

typedef struct filestatus_t {
    char name[MAX_FILENAME_BYTE];
    int inode;
    int mode;
    int size;
    int index_in_block;
} filestatus_t; //128 bytes


// ========================================================

// read block k from disk (virtual disk) into buffer block.
// size of the block is BLOCKSIZE.
// space for block must be allocated outside of this function.
// block numbers start from 0 in the virtual disk. 
int read_block (void *block, int k)
{
    int n;
    int offset;

    offset = k * BLOCKSIZE;
    lseek(vdisk_fd, (off_t) offset, SEEK_SET);
    n = read (vdisk_fd, block, BLOCKSIZE);
    if (n != BLOCKSIZE) {
	printf ("read error\n");
	return -1;
    }
    return (0); 
}

// write block k into the virtual disk. 
int write_block (void *block, int k)
{
    int n;
    int offset;

    offset = k * BLOCKSIZE;
    lseek(vdisk_fd, (off_t) offset, SEEK_SET);
    n = write (vdisk_fd, block, BLOCKSIZE);
    if (n != BLOCKSIZE) {
	printf ("write error\n");
	return (-1);
    }
    return 0; 
}

int find_empty_section (void *sec, int *block_num) {
    *block_num = ROOT_BLOCK_START;
    while (*block_num < ROOT_BLOCK_START + 4) {
        read_block(sec, *block_num);
        for (int i = 0; i < 32; i++) {
            if (*((uint32_t*)sec + i*128) == 0) {
                return i;
            }
        }
        *block_num++;
    }
    return -1; //no found empty
}

filestatus_t find_file_block_byname (char *name, void *sec, int *block_num) {
    filestatus_t file_status;
    *block_num = ROOT_BLOCK_START;
    while (*block_num < ROOT_BLOCK_START + 4) {
        read_block(sec, *block_num);
        for (int i = 0; i < 32; i++) {
            if (memcmp((char*)((uint32_t*)sec + i*128), name, strlen(name)) == 0) {
                memcpy(&file_status, ((uint32_t*)sec + i*128), sizeof(file_status));
                return file_status;
            }
        }
        *block_num++;
    }
    file_status.inode = -1;
    return file_status; //no found
}

filestatus_t find_file_block_byinode (int fd, void *sec, int *block_num) {
    filestatus_t file_status;
    *block_num = ROOT_BLOCK_START;
    while (*block_num < ROOT_BLOCK_START + 4) {
        read_block(sec, *block_num);
        for (int i = 0; i < 32; i++) {
            memcpy(&file_status, ((uint32_t*)sec + i*128), sizeof(file_status));
            if (file_status.inode == fd) {
                return file_status;
            }
        }
        *block_num++;
    }
    file_status.inode = -1;
    return file_status; //no found
}

/**********************************************************************
   The following functions are to be called by applications directly. 
***********************************************************************/

// this function is partially implemented.
int create_format_vdisk (char *vdiskname, unsigned int m)
{
    char command[1000];
    int size;
    int num = 1;
    int count;
    size  = num << m;
    count = size / BLOCKSIZE;
    //    printf ("%d %d", m, size);
    sprintf (command, "dd if=/dev/zero of=%s bs=%d count=%d",
             vdiskname, BLOCKSIZE, count);
    //printf ("executing command = %s\n", command);
    system (command);

    // now write the code to format the disk below.
    // .. your code...
    
    return (0); 
}


// already implemented
int sfs_mount (char *vdiskname)
{
    // simply open the Linux file vdiskname and in this
    // way make it ready to be used for other operations.
    // vdisk_fd is global; hence other function can use it. 
    vdisk_fd = open(vdiskname, O_RDWR); 
    return(0);
}


// already implemented
int sfs_umount ()
{
    fsync (vdisk_fd); // copy everything in memory to disk
    close (vdisk_fd);
    return (0); 
}


int sfs_create(char *filename) {
    void *sec = malloc(BLOCKSIZE);
    int block_num = -1;
    int index = find_empty_section (sec, &block_num);
    filestatus_t file_status;
    if (index != -1 && block_num < ROOT_BLOCK_START + 4 && strlen(filename) < MAX_FILENAME_BYTE) {
        memset(&file_status, 0, sizeof(file_status));
        memcpy(file_status.name, filename, strlen(filename)); //name
        file_status.index_in_block = index;
        file_status.inode = (block_num+4)*BLOCKSIZE/128 + index;
        memcpy((void*)((uint32_t*)sec + index*128), &file_status, sizeof(file_status)); //write to block
        write_block(sec, block_num);
        free(sec);
        return 0;
    }
    free(sec);
    return -1;
}

int sfs_open(char *file, int mode) {
    int block_num = -1;
    void *sec = malloc(BLOCKSIZE);
    filestatus_t file_status = find_file_block_byname(file, sec, &block_num);

    //need to check if the file is appending
    if (block_num < ROOT_BLOCK_START + 4) {
        if (mode == MODE_APPEND) {
            if (file_status.mode == NOTHING_MODE) {
                file_status.inode = APPENDING_MODE;
                memcpy((void*)((uint32_t*)sec + file_status.index_in_block*128), &file_status, sizeof(file_status)); //write to block
                write_block(sec, block_num);
                free(sec);
                return file_status.inode;
            }
        }
        else {
            if (file_status.mode == NOTHING_MODE) {
                file_status.inode = READING_MODE;
                memcpy((void*)((uint32_t*)sec + file_status.index_in_block*128), &file_status, sizeof(file_status)); //write to block
                write_block(sec, block_num);
                free(sec);
                return file_status.inode;
            }
            else if (file_status.mode == READING_MODE) {
                free(sec);
                return file_status.inode;
            }
        }
    }

    free(sec);
    return -1;
}

int sfs_close(int fd) {
    int block_num = -1;
    void *sec = malloc(BLOCKSIZE);
    filestatus_t file_status = find_file_block_byinode(fd, sec, &block_num);

    if (block_num < ROOT_BLOCK_START + 4) {
        file_status.mode = NOTHING_MODE;
        memcpy((void*)((uint32_t*)sec + file_status.index_in_block*128), &file_status, sizeof(file_status)); //write to block
        write_block(sec, block_num);
        free(sec);
        return 1;
    }

    free(sec);
    return -1;
}

int sfs_getsize (int fd) {
    int block_num = -1;
    void *sec = malloc(BLOCKSIZE);
    filestatus_t file_status = find_file_block_byinode(fd, sec, &block_num);

    free(sec);
    return file_status.size;
}

int sfs_read(int fd, void *buf, int n){
    int block_num = -1;
    void *sec = malloc(BLOCKSIZE);
    filestatus_t file_status = find_file_block_byinode(fd, sec, &block_num);
    char fcb[128];

    //need to check if the file is reading
    if (block_num < ROOT_BLOCK_START + 4) {
        if (file_status.mode == READING_MODE) {
            read_block(sec, block_num + 4);
            memcpy(fcb, (void*)((uint32_t*)sec + file_status.index_in_block*128), 128);
            memcpy(buf, fcb, n);
            free(sec);
            return file_status.inode;
        }
    }

    free(sec);
    return -1;
}


int sfs_append(int fd, void *buf, int n) {
    int block_num = -1;
    void *sec = malloc(BLOCKSIZE);
    filestatus_t file_status = find_file_block_byinode(fd, sec, &block_num);
    char fcb[128];

    //need to check if the file is appending
    if (block_num < ROOT_BLOCK_START + 4) {
        if (file_status.mode == APPENDING_MODE) {
            read_block(sec, block_num + 4);
            memcpy(fcb, buf, n);
            file_status.size += n;
            memcpy((void*)((uint32_t*)sec + file_status.index_in_block*128), fcb, 128);
            write_block(sec, block_num + 4);
            free(sec);
            return file_status.inode;
        }
    }

    free(sec);
    return -1;
}

int sfs_delete(char *filename) {
    int block_num = -1;
    void *sec = malloc(BLOCKSIZE);
    filestatus_t file_status = find_file_block_byname(file, sec, &block_num);

    if (block_num < ROOT_BLOCK_START + 4) {
        read_block(sec, block_num + 4);
        memset((void*)((uint32_t*)sec + file_status.index_in_block*128), 0, 128);
        write_block(sec, block_num + 4);

        read_block(sec, block_num);
        memset((void*)((uint32_t*)sec + file_status.index_in_block*128), 0, 128);
        write_block(sec, block_num);
        
        free(sec);
        return file_status.inode;
    }

    free(sec);
    return -1;
}