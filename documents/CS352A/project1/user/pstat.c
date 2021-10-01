#include "kernel/types.h"
#include "kernel/pstat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    struct pstat s_pstat;
    memset(&s_pstat, 0, sizeof(s_pstat));

    //call systemcall to get processes statistics
    getpstat(&s_pstat);
    int i;

    printf("pid    ticks    queue\n");
    //print processes statistics
    for (i = 0; i < NPROC; i++)
    {
        if (s_pstat.inuse[i] == 1)
        {
            printf("%d      %d       %d\n", s_pstat.pid[i], s_pstat.ticks[i], s_pstat.queue[i]);
        }
    }
    exit(0);
}