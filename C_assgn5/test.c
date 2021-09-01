#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define clocks rdtsc
#define TICKS  1800000000

static inline uint64_t rdtsc() {
	uint32_t lo, hi;
	__asm__ __volatile__ ("xorl %%eax, %%eax\n cpuid\n rdtsc\n"
	: "=a" (lo), "=d" (hi)
	:
	: "%ebx", "%ecx");
	return(uint64_t)hi << 32 | lo;
}

#define ITERS 1000000
static double cal_iter_time(void) {
	//start timing!
	time_t start, total;
	start = clocks();
    double var;
	for (volatile int i = 0; i < ITERS; ++i){
        var = 21.667;
	}
	//get time for timed operation AND looping
	total = clocks() - start;

//#if 0
	start = clocks();
	for (volatile int i = 0; i < ITERS; ++i){
		//don't actually do anything here, this measures loop overhead
	}
	//subtract off loop overhead!
	total -= (clocks() - start);
//#endif
printf("ttt %ld %lf\n", total, (double)ITERS/total*TICKS);
start = clocks();
sleep(1);
printf("teest %ld\n", clocks() - start);
	return (double)total/(double)TICKS;
}

int main(int argc, char **argv)
{
    printf("get FLOP: %lf\n", cal_iter_time());

    return 0;
}
