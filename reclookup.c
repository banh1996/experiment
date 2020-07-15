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
static char line[LINELEN];

static void wordsInFile(int fd)
{
    int count_line = 0;
    char arr;
#if 0
    while (read(fd, &g_info[1], sizeof(file_struct_t)*(BUF_SIZE-1)) > 0) {
        count_line++;
    }
    printf("hungtn16 %d\n", count_line);
#endif
    while (read(fd, &arr, 1))
    {
        if (arr != '\n')
        {
            lseek(fd, 1, SEEK_CUR);
            printf("%c", arr);
        }
    } 
    printf("\n");
}

static void write_output(int fd)
{
#if 0
    memcpy(g_info[0].id, "id", 2);
    memcpy(g_info[0].fname, "first_name", 10);
    memcpy(g_info[0].mname, "middle_name", 11);
    memcpy(g_info[0].lname, "last_name", 9);
    memcpy(g_info[0].street, "street", 6);
    memcpy(g_info[0].city, "city", 4);
    memcpy(g_info[0].zip, "zip", 3);
    memcpy(g_info[0].country_code, "country", 7);
    memcpy(g_info[0].email, "email", 5);
    memcpy(g_info[0].phone, "phone", 5);
#endif   
    int i = 1;
    memcpy(&line[strlen(line)], "id,", 3);
    memcpy(&line[strlen(line)], "first_name,", 11);
    memcpy(&line[strlen(line)], "middle_name,", 12);
    memcpy(&line[strlen(line)], "last_name,", 10);
    memcpy(&line[strlen(line)], "street,", 7);
    memcpy(&line[strlen(line)], "city,", 5);
    memcpy(&line[strlen(line)], "zip,", 4);
    memcpy(&line[strlen(line)], "country,", 8);
    memcpy(&line[strlen(line)], "email,", 6);
    memcpy(&line[strlen(line)], "phone\n", 6);
    write(fd, line, strlen(line));
    while (g_info[i].id[0])
    {
        memset(line, 0, sizeof(line));
        memcpy(&line[strlen(line)], g_info[i].id, strlen(g_info[i].id));
        memcpy(&line[strlen(line)], ",", 1);
        memcpy(&line[strlen(line)], g_info[i].fname, strlen(g_info[i].fname));
        memcpy(&line[strlen(line)], ",", 1);
        memcpy(&line[strlen(line)], g_info[i].mname, strlen(g_info[i].mname));
        memcpy(&line[strlen(line)], ",", 1);
        memcpy(&line[strlen(line)], g_info[i].lname, strlen(g_info[i].lname));
        memcpy(&line[strlen(line)], ",", 1);
        memcpy(&line[strlen(line)], g_info[i].street, strlen(g_info[i].street));
        memcpy(&line[strlen(line)], ",", 1);
        memcpy(&line[strlen(line)], g_info[i].city, strlen(g_info[i].city));
        memcpy(&line[strlen(line)], ",", 1);
        memcpy(&line[strlen(line)], g_info[i].zip, strlen(g_info[i].zip));
        memcpy(&line[strlen(line)], ",", 1);
        memcpy(&line[strlen(line)], g_info[i].country_code, strlen(g_info[i].country_code));
        memcpy(&line[strlen(line)], ",", 1);
        memcpy(&line[strlen(line)], g_info[i].email, strlen(g_info[i].email));
        memcpy(&line[strlen(line)], ",", 1);
        memcpy(&line[strlen(line)], g_info[i].phone, strlen(g_info[i].phone));
        memcpy(&line[strlen(line)], "\n", 1);
        write(fd, line, strlen(line));
        i++;
    }
}

int main(int argc, char *argv[])
{
    char check_if_have_input = 0;
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
                // fprintf(stdout, "file input --> %s\n", optarg);
                wordsInFile(fd);
                close(fd);
            }
            check_if_have_input = 1;
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
        default:
            fprintf(stderr, "Usage: %s [-d delim] -f file1 [[-f file2] ... [-f fileN]]\n"
                    , argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    if (check_if_have_input == 0)
    {
        printf("error: no -i\n");
        exit(3);
    }

    return EXIT_SUCCESS;
}
