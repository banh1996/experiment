#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <errno.h> 


int main(int argc, char *argv[])
{
    int opt = 0;
    int fd, count = 0;
    while ((opt = getopt(argc, argv, "n:")) != -1) {
        switch (opt) {
        case 'n':
            count = atoi(optarg);
            break;
        default:
            break;
        }
    }

    return 0;
}
