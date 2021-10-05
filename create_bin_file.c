#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
    char data[200];
    int fd = open ("gifts.dat", O_CREAT | O_WRONLY);
    int i, line = 1000000;

    memset(data, 0x18, sizeof(data));
    data[sizeof(data)-1] = '\n';

    for (i = 0; i < line; i++)
        write(fd, data, sizeof(data));

    close(fd);

    return 0;
}
