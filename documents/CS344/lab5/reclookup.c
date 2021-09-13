#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <errno.h> 
#include "file_struct.h"

static char line[500];
static file_struct_t g_info;

static void write_output(int fd)
{
    memset(line, 0, sizeof(line));
    sprintf(line, "id: %s\n", g_info.id);
    write(fd, line, strlen(line));
    memset(line, 0, sizeof(line));
    sprintf(line, " first_name: %s\n", g_info.fname);
    write(fd, line, strlen(line));
    memset(line, 0, sizeof(line));
    sprintf(line, " middle_name: %s\n", g_info.mname);
    write(fd, line, strlen(line));
    memset(line, 0, sizeof(line));
    sprintf(line, " last_name: %s\n", g_info.lname);
    write(fd, line, strlen(line));
    memset(line, 0, sizeof(line));
    sprintf(line, " street: %s\n", g_info.street);
    write(fd, line, strlen(line));
    memset(line, 0, sizeof(line));
    sprintf(line, " city: %s\n", g_info.city);
    write(fd, line, strlen(line));
    memset(line, 0, sizeof(line));
    sprintf(line, " zip: %s\n", g_info.zip);
    write(fd, line, strlen(line));
    memset(line, 0, sizeof(line));
    sprintf(line, " country: %s\n", g_info.country_code);
    write(fd, line, strlen(line));
    memset(line, 0, sizeof(line));
    sprintf(line, " email: %s\n", g_info.email);
    write(fd, line, strlen(line));
    memset(line, 0, sizeof(line));
    sprintf(line, " phone: %s\n", g_info.phone);
    write(fd, line, strlen(line));
}

int main(int argc, char *argv[])
{
    char check_if_have_input = 0;
    int opt = 0, index = 0;
    int fd_input, fd_output = STDOUT_FILENO;
    memset(&g_info, 0, sizeof(g_info));
    while ((opt = getopt(argc, argv, "i:o:h:")) != -1) {
        switch (opt) {
        case 'i':
            fd_input = open(optarg, O_RDONLY);
            if(fd_input==-1){
                printf("file not found.\n");
                return -1;
            }
            check_if_have_input = 1;
            break;
        case 'o':
            fd_output = open(optarg, O_WRONLY|O_CREAT|O_TRUNC,  S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
            if(fd_output==-1){
                printf("file cannot create.\n");
                return -1;
            }
            break;
        case 'h':
            fprintf(stdout, " [-i <input file>] [-o <output file>] [-h] [-v]\n");
            break;
        default:
            fprintf(stderr, "Usage: %s [-d delim] -f file1 [[-f file2] ... [-f fileN]]\n"
                    , argv[0]);
            exit(7);
        }
    }

    if (check_if_have_input == 0)
    {
        printf("error: lack of -i\n");
        exit(3);
    }
    index = atoi( argv[argc-1]);
    lseek(fd_input, sizeof(file_struct_t)*index, SEEK_CUR);
    while (read(fd_input, &g_info, sizeof(file_struct_t)) > 0) {
        write_output(fd_output);
        break;
    }
    close(fd_input);
    if (fd_output != STDOUT_FILENO)
        close(fd_output);

    return EXIT_SUCCESS;
}
