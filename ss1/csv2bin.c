#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <errno.h> 
#include "file_struct.h"

#define LINELEN 1024
#define BUF_SIZE 100

// I'm using far more then JUST whitespace as delimiters
#define DELIMITERS " \t.-+,?!\n:;"

static file_struct_t g_info[BUF_SIZE];
static int g_line = 0;

static void copy_info(char *str, int len, int index, int line)
{
    if (len)
    {
        switch (index)
        {
        case 0:
            memcpy(g_info[line].id, str, len);
            break;
        case 1:
            memcpy(g_info[line].fname, str, len);
            break;
        case 2:
            memcpy(g_info[line].mname, str, len);
            break;
        case 3:
            memcpy(g_info[line].lname, str, len);
            break;
        case 4:
            memcpy(g_info[line].street, str, len);
            break;
        case 5:
            memcpy(g_info[line].city, str, len);
            break;
        case 6:
            memcpy(g_info[line].zip, str, len);
            break;
        case 7:
            memcpy(g_info[line].country_code, str, len);
            break;
        case 8:
            memcpy(g_info[line].email, str, len);
            break;
        case 9:
            memcpy(g_info[line].phone, str, len);
            break;
        
        default:
            break;
        }
    }
}

static void wordsInFile(int fd, char *delimiters)
{
    char line[LINELEN] = {0};
    char *token = NULL;
    int  count_line = 0, i = 0, index = 0;

    while (read(fd, &line[i], 1) == 1) {
    /* end of line */
        if (line[i] == '\n' || line[i] == 0x0) {
            line[i] = 0;
            index = 0;
            token = strtok(line, delimiters);
            while (token != NULL && token[strlen(token)] != '\n') {
                fprintf(stdout, "word --> %s\n", token);
                copy_info(token, strlen(token), index, count_line);
                token = strtok(NULL, delimiters);
                index++;
            }
            fprintf(stdout, "line\n");
            count_line++;
            i = 0;
            continue;
        }
        i++;
    }
    g_line = count_line;
}

static void write_output(int fd)
{
    write(fd, &g_info[1], sizeof(file_struct_t)*(g_line - 1));
}

int main(int argc, char *argv[])
{
    int opt = 0;
    int fd;
    memset(g_info, 0, sizeof(g_info));
    while ((opt = getopt(argc, argv, "i:o:h:v:")) != -1) {
        switch (opt) {
        case 'i':
            fd = open(optarg, O_RDONLY);
            if(fd==-1){
                printf("file not found.\n");
                return -1;
            }
            else {
                fprintf(stdout, "file input --> %s\n", optarg);
                wordsInFile(fd, ",\n");
                close(fd);
            }
            break;
        case 'o':
            fd = open(optarg, O_WRONLY|O_CREAT|O_TRUNC,  S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
            if(fd==-1){
                printf("file cannot create.\n");
                return -1;
            }
            else {
                fprintf(stdout, "file output --> %s\n", "out");
                write_output(fd);
                close(fd);
            }
            break;
        case 'h':
            fprintf(stdout, " [-i <input file>] [-o <output file>] [-h] [-v]\n");
            break;
        case 'v':
            fprintf(stdout, "verbose: verbose enabled: 1\n");
            // fprintf(stdout, "verbose: using out as input 63\n");
            // fprintf(stdout, "verbose: using sample as output 78\n");
            // fprintf(stdout, "verbose: exiting read loop: 100\n");
            break;
        default:
            fprintf(stderr, "Usage: %s [-d delim] -f file1 [[-f file2] ... [-f fileN]]\n"
                    , argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}
