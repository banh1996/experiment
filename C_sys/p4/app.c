#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "simplefs.h"

int main(int argc, char **argv)
{
    int ret;
    int fd1, fd2, fd; 
    int i;
    char c; 
    char buffer[16384];
    char buffer_read[16384];
    char buffer2[8] = {50, 50, 50, 50, 50, 50, 50, 50};
    int size;
    char vdiskname[200]; 

    printf ("started\n");

    if (argc != 2) {
        printf ("usage: app  <vdiskname>\n");
        exit(0);
    }
    strcpy (vdiskname, argv[1]); 
    
    ret = sfs_mount (vdiskname);
    if (ret != 0) {
        printf ("could not mount \n");
        exit (1);
    }

    printf ("creating files\n"); 
    sfs_create ("file1.bin");
    sfs_create ("file2.bin");
    sfs_create ("file3.bin");

clock_t start_time = clock();
/*
char testbuf[24];
memset(testbuf, 0, sizeof(testbuf));
for (int j = 0; j < 5; j++){
	sprintf(testbuf, "test%d.bin", j);
	printf("ef %s\n",testbuf);
	sfs_create (testbuf);
}
printf("create take time %ld\n", clock() - start_time);
*/
    sfs_create ("test.bin");
    int fd_test = sfs_open ("test.bin", MODE_APPEND);

start_time = clock();
usleep(100000);
clock_t ttt = clock() - start_time;
printf("test clock %ld %ld %ld %ld\n", ttt, start_time, clock(), CLOCKS_PER_SEC);

    sprintf(buffer, "1234567890asdfghjklzxcvbnmqwertyuiop0987654321");
    printf("buffer write: %s\n", buffer);
start_time = clock();
    sfs_append (fd_test, (void *) buffer, sizeof(buffer));
printf("write take time %ld\n", clock() - start_time);
    sfs_close (fd_test);

    fd_test = sfs_open ("test.bin", MODE_READ);
start_time = clock();
    sfs_read (fd_test, (void *) buffer_read, sizeof(buffer_read));
    printf("buffer read: %s\n", buffer_read);
printf("read take time %ld\n", clock() - start_time);
    sfs_close (fd_test);

    fd1 = sfs_open ("file1.bin", MODE_APPEND);
    fd2 = sfs_open ("file2.bin", MODE_APPEND);
    for (i = 0; i < 10000; ++i) {
        buffer[0] =   (char) 65;
        sfs_append (fd1, (void *) buffer, 1);
    }

    for (i = 0; i < 10000; ++i) {
        buffer[0] = (char) 65;
        buffer[1] = (char) 66;
        buffer[2] = (char) 67;
        buffer[3] = (char) 68;
        sfs_append(fd2, (void *) buffer, 4);
    }
    
    sfs_close(fd1);
    sfs_close(fd2);

    fd = sfs_open("file3.bin", MODE_APPEND);
    for (i = 0; i < 10000; ++i) {
        memcpy (buffer, buffer2, 8); // just to show memcpy
        sfs_append(fd, (void *) buffer, 8);
    }
    sfs_close (fd);

    fd = sfs_open("file3.bin", MODE_READ);
    printf("size open %d\n", fd);
    size = sfs_getsize (fd);
    for (i = 0; i < size; ++i) {
        sfs_read (fd, (void *) buffer, 1);
        c = (char) buffer[0];
        c = c + 1;
    }
    sfs_close (fd);
    ret = sfs_umount();
}
