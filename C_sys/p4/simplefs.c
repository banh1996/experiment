#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include "simplefs.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

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

// set bit in bitmap blocks
void set_bit_map(int index) {
    void *sec = malloc(BLOCKSIZE);
    int block_num = index/BLOCKSIZE + 1;
    read_block(sec, block_num); //read bitmap
    *((uint32_t*)sec + index/32) |= (uint32_t)(1 << (index%32));
    write_block(sec, block_num);
    free(sec);
}


// clear bit in bitmap blocks
void clear_bit_map(int index) {
    void *sec = malloc(BLOCKSIZE);
    int block_num = index/BLOCKSIZE + 1;
    read_block(sec, block_num); //read bitmap
    *((uint32_t*)sec + index/32) &= ~(uint32_t)(1 << (index%32));
    write_block(sec, block_num);
    free(sec);
}

//find bit 0 in bitmap
int find_empty_bit(void *sec) {
    for (uint32_t i = 0; i < BLOCKSIZE/32; i++) {
        int temp = *(int*)((uint32_t*)sec + i);
        temp = ~temp;
        int cnt = 0;
        if (temp)
            while (!(temp & (1 << cnt++)));
        if (cnt != 0)
            return (i*32 + cnt - 1);
    }
    return -1;
}

//find empty block
int find_empty_block() {
    void *sec = malloc(BLOCKSIZE);
    for (int i = 1; i <= 4; i++) {
        read_block(sec, i); //read bitmap 1
        int index = find_empty_bit(sec);
        if (index != -1) {
            free(sec);
            return (index + (i-1)*BLOCKSIZE);
        }
    }
    free(sec);
    return -1;
}

//find empty section(128bytes) in block
int find_empty_section_in_block (void *sec, int *block_num) {
    *block_num = ROOT_BLOCK_START;
    while (*block_num < ROOT_BLOCK_START + 4) {
        read_block(sec, *block_num);
        for (int i = 0; i < 32; i++) {
            if (*((uint32_t*)sec + i*128) == 0) {
                return i;
            }
        }
        (*block_num)++;
    }
    *block_num = ROOT_BLOCK_START + 4;
    return -1; //no found empty
}

//find filestatus in root directory by its name
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
        (*block_num)++;
    }
    file_status.inode = -1;
    return file_status; //no found
}

//find filestatus in root directory by its fd
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
        (*block_num)++;
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
    sfs_mount (vdiskname);
    for (int i = 0; i <= 9; i++)
        set_bit_map(i);
    sfs_umount();
    
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
    filestatus_t file_status = find_file_block_byname(filename, sec, &block_num);
    if (block_num < ROOT_BLOCK_START + 4)
        return -1;

    int index = find_empty_section_in_block (sec, &block_num);
    //filestatus_t file_status;
    if (index != -1 && block_num < ROOT_BLOCK_START + 4 && strlen(filename) < MAX_FILENAME_BYTE) {
        memset(&file_status, 0, sizeof(file_status));
        memcpy(file_status.name, filename, strlen(filename)); //name
        file_status.index_in_block = index;
        file_status.inode = find_empty_block();
        set_bit_map(file_status.inode);
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
                file_status.mode = APPENDING_MODE;
                memcpy((void*)((uint32_t*)sec + file_status.index_in_block*128), &file_status, sizeof(file_status)); //write to block
                write_block(sec, block_num);
                free(sec);
                return file_status.inode;
            }
        }
        else {
            if (file_status.mode == NOTHING_MODE) {
                file_status.mode = READING_MODE;
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
        return 0;
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
    int fcb_index[1024];

    //need to check if the file is appending
    memset(buf, 0, n);
    if (block_num < ROOT_BLOCK_START + 4) {
        if (file_status.mode == READING_MODE) {
            read_block(sec, file_status.inode);
            memcpy((void*)fcb_index, sec, BLOCKSIZE);

            //read data
            int remain_len = n, i = 0, temp_len=0;
            while(i < 1024 && remain_len > 0) {
                if (fcb_index[i] != 0) {
                    read_block(sec, fcb_index[i]);
                    uint32_t sec_len = *(uint32_t*)sec;
                    if (sec_len <= BLOCKSIZE) {
                        memcpy((char*)buf + temp_len, (void*)((uint8_t*)sec + 4), MIN(remain_len, sec_len - 4));
			temp_len += MIN(remain_len, sec_len - 4);
                        remain_len = remain_len - MIN(remain_len, sec_len - 4);
                    }
                }
                else
                    break;
                i++;
            }

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
    int fcb_index[1024];
    //need to check if the file is appending
    if (block_num < ROOT_BLOCK_START + 4) {
        if (file_status.mode == APPENDING_MODE) {
            read_block(sec, file_status.inode);
            memcpy((void*)fcb_index, sec, BLOCKSIZE);
            file_status.size += n;
            read_block(sec, block_num);
            memcpy((void*)((uint32_t*)sec + file_status.index_in_block*128), &file_status, sizeof(file_status)); //write to block
            write_block(sec, block_num);

            //write data
            int remain_len = n, i = 0;
            while(i < 1024 && remain_len > 0) {
                if (fcb_index[i] != 0) {
                    read_block(sec, fcb_index[i]);
                    uint32_t sec_len = *(uint32_t*)sec;
                    if (sec_len < BLOCKSIZE) {
                        memcpy((void*)((uint8_t*)sec + sec_len), buf, MIN(remain_len, BLOCKSIZE - sec_len));
                        sec_len += MIN(remain_len, BLOCKSIZE - sec_len);
                        memcpy (sec, &sec_len, 4);
                        remain_len = remain_len - MIN(remain_len, BLOCKSIZE - sec_len);
                    }
                }
                else { //index for new block
                    fcb_index[i] = find_empty_block();
                    set_bit_map(fcb_index[i]);
                    uint32_t sec_len = 4;
                    read_block(sec, fcb_index[i]);
                    memcpy((void*)((uint8_t*)sec + sec_len), buf, MIN(remain_len, BLOCKSIZE - sec_len));
                    sec_len += MIN(remain_len, BLOCKSIZE - 4);
                    memcpy (sec, &sec_len, 4);
                    remain_len = remain_len - MIN(remain_len, BLOCKSIZE);
                }
                write_block(sec, fcb_index[i]);
                i++;
            }

            //write fcb table
            memcpy(sec, fcb_index, BLOCKSIZE);
            write_block(sec, file_status.inode);
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
    filestatus_t file_status = find_file_block_byname(filename, sec, &block_num);
    int fcb_index[1024];

    if (block_num < ROOT_BLOCK_START + 4) {
        read_block(sec, file_status.inode);
        memcpy((void*)fcb_index, sec, BLOCKSIZE);

        int i = 0;
        memset(sec, 0, BLOCKSIZE);
        while(i < 1024) {
            if (fcb_index[i] != 0) {
                clear_bit_map(fcb_index[i]);
                write_block(sec, fcb_index[i]);
            }
            else
                break;
            i++;
        }
        write_block(sec, file_status.inode);

        read_block(sec, block_num);
        memset((void*)((uint32_t*)sec + file_status.index_in_block*128), 0, 128);
        clear_bit_map(block_num);
        write_block(sec, block_num);

        free(sec);
        return file_status.inode;
    }

    free(sec);
    return -1;
}
