#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "simplefs.h"

#define MAX_FILES_NUMBER 16
#define MAX_FILENAME_BYTE 110
// Global Variables =======================================
int vdisk_fd; // Global virtual disk file descriptor. Global within the library.
              // Will be assigned with the vsfs_mount call.
              // Any function in this file can use this.
              // Applications will not use  this directly. 
typedef enum filemode_t {
    NOTHING = 0,
    APPENDING,
    READING
} filemode_t;

typedef struct filestatus_t {
    char name[MAX_FILENAME_BYTE];
    int fd;
    filemode_t mode;
} filestatus_t;

typedef struct filetable_t {
    filestatus_t files[MAX_FILES_NUMBER];
    int cur_num;
} filetable_t;

filetable_t g_filetable;
// ========================================================

int find_file_mode_by_name (char *name) {
    for (int i = 0; i < MAX_FILES_NUMBER; i++) {
        if (memcmp(g_filetable.files[i].name, name, strlen(name)) == 0)
            return i;
    }
    return MAX_FILES_NUMBER;
}

int find_file_mode_by_fd (int fd) {
    for (int i = 0; i < MAX_FILES_NUMBER; i++)
    {
        if (g_filetable.files[i].fd == fd)
            return i;
    }
    return MAX_FILES_NUMBER;
}

int get_empty_index_file_table (void) {
    for (int i = 0; i < MAX_FILES_NUMBER; i++) {
        if (g_filetable.files[i].mode == NOTHING)
            return i;
    }
    return MAX_FILES_NUMBER;
}

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
    read_block(&block, k);
    write_block(block, k);
    int ret = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH);
    if (ret != -1)
        ret = close (vdisk_fd);
    return ret;
}

int sfs_open(char *file, int mode)
{
    int ret = -1, empty_index = MAX_FILES_NUMBER;
    int file_index = find_file_mode_by_name(file);
    
    if (file_index == MAX_FILES_NUMBER)
        return -1;
    //need to check if the file is appending
    if (mode == MODE_APPEND)
    {
        if (g_filetable.files[file_index].mode == NOTHING)
        {
            ret = open(file, O_APPEND, S_IRUSR | S_IRGRP | S_IROTH);
            empty_index = get_empty_index_file_table();
            g_filetable.files[empty_index].fd = ret;
            g_filetable.files[empty_index].mode = APPENDING;
            memcpy(g_filetable.files[empty_index].name, file, strlen(file));
        }
    }
    else
    {
        if (g_filetable.files[file_index].mode == NOTHING || g_filetable.files[file_index].mode == READING)
        {
            ret = open(file, O_RDONLY, S_IRUSR | S_IRGRP | S_IROTH);
            empty_index = get_empty_index_file_table();
            g_filetable.files[empty_index].fd = ret;
            g_filetable.files[empty_index].mode = READING;
            memcpy(g_filetable.files[empty_index].name, file, strlen(file));
        }
    }
    return ret; 
}

int sfs_close(int fd){
    int file_index = find_file_mode_by_fd(fd);
    if (file_index == MAX_FILES_NUMBER)
        return -1;
    if (g_filetable.files[file_index].mode != NOTHING) {
        g_filetable.files[file_index].fd = 0;
        g_filetable.files[file_index].mode = NOTHING;
        memset(g_filetable.files[file_index].name, 0, sizeof(g_filetable.files[file_index].name));
    }
    int ret = close (vdisk_fd);
    return ret;
}

int sfs_getsize (int fd)
{
    struct stat st;
    int ret = fstat(fd, &st);
    if (ret == 0)
        return st.st_size;
    return ret;
}

int sfs_read(int fd, void *buf, int n){
    int file_index = find_file_mode_by_fd(fd);
    if (file_index == MAX_FILES_NUMBER)
        return -1;

    struct stat st;
    int ret = fstat(fd, &st);
    if (ret == 0)
    {
        int size = read(fd, buf, n);
        return size;
    }
    return ret;
}


int sfs_append(int fd, void *buf, int n) {
    int file_index = find_file_mode_by_fd(fd);
    if (file_index == MAX_FILES_NUMBER)
        return -1;

    filemode_t cur_mode = check_file_mode(fd);
    int size = write(fd, buf, n);
    return size;
}

int sfs_delete(char *filename) {
    if (remove(filename) == 0)
        return (0);
    return (-1);
}