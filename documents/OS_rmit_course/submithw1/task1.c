#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include "common_def.h"


static int TaskFilter(char *f_in, char *f_out)
{
    int fd_in = open(f_in, O_RDONLY);
    int fd_out = open(f_out, O_RDWR | O_CREAT, 0666);
    int read_bytes;
    int file_read_stop = 0;
    int is_keep_this_line = 0x01;
    int indexCurrentSymbol = 0;
    char buf[BUFFSIZE*10];

    while (file_read_stop == 0)
    {
        read_bytes = read(fd_in, &buf[indexCurrentSymbol], 1); 
        if (read_bytes == -1) 
        {
            fprintf(stderr, "read %s while: -1", f_in);
            break;
        }

        if (read_bytes == 0)
        {
            file_read_stop = 1;
        }

        if (buf[indexCurrentSymbol] == DELIM_STR || buf[indexCurrentSymbol] == EOF)
        {
            //TODO
            if (indexCurrentSymbol < 3 || indexCurrentSymbol > 15)
                is_keep_this_line = 0;
            for (int i = 0; i < indexCurrentSymbol; i++)
            {
                if (buf[i] > 'z' || buf[i] < 'a')
                    is_keep_this_line = 0;
            }
            if (is_keep_this_line == 0x01)
            {
                //fprintf(stdout, "%s", buf);
                write(fd_out, buf, indexCurrentSymbol+1);
            }
            indexCurrentSymbol = 0;
            is_keep_this_line = 0x01;
            memset(buf, 0, sizeof(buf));
        }
        else
        {
            indexCurrentSymbol++;
        }
    }
    close(fd_in);
    close(fd_out);
    return 0;
}

static int clean_garbage(char *name)
{
    remove(name);
    for (int i = 3; i < 16; i++)
    {
        char file[15] = "wordfile\0\0\0";
        sprintf(&file[strlen(file)], "%d", i);
        sprintf(&file[strlen(file)], ".txt");
        remove(file);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "lack of argument\n");
        return -1;
    }
    clean_garbage(argv[2]);
    TaskFilter(argv[1], argv[2]);
    return 0;
}
