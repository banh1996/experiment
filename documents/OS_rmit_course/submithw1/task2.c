#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include "common_def.h"
#include <sys/wait.h>

static int readline (char *buf, int fd_in)
{
    //int fd_in = open(f_in, O_RDONLY);
    int read_bytes;
    int indexCurrentSymbol = 0;

    while (1)
    {
        read_bytes = read(fd_in, &buf[indexCurrentSymbol], 1); 
        if (read_bytes == -1) 
        {
            fprintf(stderr, "read %d while: -1\n", fd_in);
            return -1;
        }

        if (read_bytes == 0)
            break;

        if (buf[indexCurrentSymbol] == DELIM_STR || buf[indexCurrentSymbol] == EOF)
        {
            indexCurrentSymbol++;
            break;
        }
        else
        {
            indexCurrentSymbol++;
        }
    }
    //close(fd_in);
    return indexCurrentSymbol;
}


static int map2(char *f_in)
{
    int fd_in = open(f_in, O_RDONLY);
    int read_bytes, fd_out[13];
    int file_read_stop = 0;
    int indexCurrentSymbol = 0;
    int ret = 0;
    char buf[BUFFSIZE];

    for (int i = 0; i < 13; i++)
    {
        char file[15] = "wordfile\0\0\0\0\0\0\0";
        sprintf(&file[strlen(file)], "%d", i+3);
        sprintf(&file[strlen(file)], ".txt");
        fd_out[i] = open(file, O_RDWR | O_CREAT, 0666);
    }

    while (file_read_stop == 0)
    {
        read_bytes = read(fd_in, &buf[indexCurrentSymbol], 1); 
        if (read_bytes == -1) 
        {
            fprintf(stderr, "read %s while: -1\n", f_in);
            break;
        }

        if (read_bytes == 0)
        {
            file_read_stop = 1;
        }

        if (buf[indexCurrentSymbol] == DELIM_STR || buf[indexCurrentSymbol] == EOF)
        {
            //TODO: export to files
            if (indexCurrentSymbol >= 3 && indexCurrentSymbol <= 15)
            {
                write(fd_out[indexCurrentSymbol-3], buf, indexCurrentSymbol+1);
            }
            indexCurrentSymbol = 0;
            memset(buf, 0, sizeof(buf));
        }
        else
        {
            indexCurrentSymbol++;
        }
    }
    close(fd_in);
    for (int i = 0; i < 13; i++)
    {
        close(fd_out[i]);
    }

    for (int i = 0; i < 13; i++)
    {
        int pid = fork();
        if (pid == 0)
        {
            char file[15] = "wordfile\0\0\0\0\0\0\0";
            sprintf(&file[strlen(file)], "%d", i+3);
            sprintf(&file[strlen(file)], ".txt");
            //printf("tt: %d\n", i);
            execlp("sort", "sort", "-f", "-k", "1.3", file, "-o", file, NULL);
        }
        else
        {
            wait(&ret);
            //break;
        }
    }

    return 0;
}

static int reduce2(char *f_out)
{
    int fd_in[13];
    int fd_out;
    int readbyte = 0;
    char buf[13][BUFFSIZE];
    char continue_reads[13];
    int temp_index = 14;
    char min_str[BUFFSIZE];

    if (memcmp(f_out, "stdout", 6) == 0)
        fd_out = STDOUT_FILENO;
    else
        fd_out = open(f_out, O_RDWR | O_CREAT, 0666);
    memset(continue_reads, 1, sizeof(continue_reads));

    for (int i = 0; i < 13; i++)
    {
        char file[15] = "wordfile\0\0\0\0\0\0\0";
        sprintf(&file[strlen(file)], "%d", i+3);
        sprintf(&file[strlen(file)], ".txt");
        fd_in[i] = open(file, O_RDONLY);
    }

    while (1)
    {
        //read line each file
        for (int i = 0; i < 13; i++)
        {
            if (continue_reads[i])
            {
                memset(&buf[i], 0, BUFFSIZE);
                if ((readbyte = readline(buf[i], fd_in[i])) > 0)
                {
                    continue_reads[i] = 0;
                    //fprintf(stdout, "%d:%s", readbyte, buf[i]);
                }
            }
        }

        //find the lowest order
        temp_index = 14;
        memset(min_str, 'z', BUFFSIZE);
        for (int i = 0; i < 13; i++)
        {
            if (continue_reads[i] == 0 && strcmp(&min_str[2], &buf[i][2]) > 0)
            {
                // printf("asd: %d %s", temp_index, buf[i]);
                memset(min_str, 0, BUFFSIZE);
                sprintf(min_str, "%s", buf[i]);
                temp_index = i;
            }
        }

        //handle the minimum character
        if (temp_index > 12)
        {
            //fprintf(stderr, "error while running reduces\n");
            break;
        }
        continue_reads[temp_index] = 1;
        //fprintf(stdout, "%s", buf[temp_index]);
        write(fd_out, buf[temp_index], temp_index+4);
    }

    for (int i = 0; i < 13; i++)
        close(fd_in[i]);

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        fprintf(stderr, "lack of argument\n");

    map2(argv[1]);
    reduce2("stdout");
    return 0;
}