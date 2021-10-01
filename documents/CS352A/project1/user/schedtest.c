#include "kernel/types.h"
#include "kernel/pstat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int ticks = 0;
    int count = 0;
    int i = 0;
    if (argc != 3) {
        printf("not enough argument number, must be 2\n");
        exit(-1);
    }

    ticks = atoi(argv[1]);
    count = atoi(argv[2]);

    printf ("testprocess %d %d\n", ticks, count);
    for (i = 0; i < count; i++) {
        sleep(1);
        fork();
        sleep(ticks);
    }
    exit(0);
}