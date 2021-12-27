#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
    int filefd;

    filefd = open("/samples/systems/fota_aurix/teeest.txt", O_RDWR | O_TRUNC | O_CREAT);

    if (filefd == -1)
    {
        printf("Can not open file");
        return -1;
    }

    write(filefd, "test ok\n", 8);
    close(filefd);

    while(1);
    return 0;
}
