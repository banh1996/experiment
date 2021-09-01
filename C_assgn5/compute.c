#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#define IP_SERVER   "127.0.0.1"
#define PORT 12345
#define DELIM_STR   '\n'
#define PRINTFF printf

static inline uint64_t rdtsc() {
	uint32_t lo, hi;
	__asm__ __volatile__ ("xorl %%eax, %%eax\n cpuid\n rdtsc\n"
	: "=a" (lo), "=d" (hi)
	:
	: "%ebx", "%ecx");
	return(uint64_t)hi << 32 | lo;
}

static int check_perfect_number(int num) {
	int count, sum = 0;
	for(count = 1; count < num; count++)
    {
        if(num % count == 0)
        {
            sum = sum + count;
        }
    }
	if(sum == num)  
        return 0;
	return -1;
}

#define clocks rdtsc
#define ITERS  10000
static double cal_iter_time(void) {
    unsigned long ticks = 0;
    struct timespec ts1 = {
       .tv_sec = 0,
       .tv_nsec = 10000000
    };
    //start timing!
    time_t start, total;
    start = clocks();

    //get ticks
    nanosleep(&ts1, NULL);
    ticks = (clocks() - start)*100;
    PRINTFF("ticks: %ld\n", ticks);

    start = clocks();
    //double var;
    for (volatile int i = 1; i <= ITERS; ++i){
        //var = 1.1;
        check_perfect_number(i);
    }
    //get time for timed operation AND looping
    total = clocks() - start;
    // start = clocks();
    // for (volatile int i = 0; i < ITERS; ++i){
    //     //don't actually do anything here, this measures loop overhead
    // }
    // //subtract off loop overhead!
    // total -= (clocks() - start);
    return (double)ITERS/total*ticks*ITERS;
}

static void *sock_monitor(void *data)
{
    int sockfd = *(int*)data;
    char buf[15];
    memset(buf, 0, sizeof(buf));
    PRINTFF("thread wait\n");
    while (1)
    {
        read(sockfd, buf, sizeof(buf));
        if (memcmp(buf, "shutdown", 8) == 0)
        {
            // send kill signal
            pid_t pid = getpid();
            kill(pid, SIGINT);
        }
    }
    PRINTFF("ext thread\n");
    pthread_exit(NULL);
}


int main(void)
{
    int sockfd;
	struct sockaddr_in servaddr;

	// socket create and varification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created...\n");
	memset(&servaddr, 0, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(IP_SERVER);
	servaddr.sin_port = htons(PORT);

	// connect the client socket to server socket
	if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server...\n");

    // processing here
	double FLOPS = cal_iter_time();
	char buf[30];
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "compute%ld", (long)FLOPS);
	write(sockfd, buf, strlen(buf));

    char *eptr;
    memset(buf, 0, sizeof(buf));
    read(sockfd, buf, sizeof(buf));
    long start_index = 0;
    for (long unsigned int i = 0; i < strlen(buf); i++)
    {
        if (buf[i] == '.')
        {
            start_index = i;
            break;
        }
    }
    char temp_buf[11];
    memset(temp_buf, 0, sizeof(temp_buf));
    memcpy(temp_buf, &buf[7], start_index - 7);
    long start_num = strtol(temp_buf, &eptr, 10);
    long end_num = strtol(&buf[start_index+1], &eptr, 10);
    PRINTFF("recv startnum|endnum: %ld|%ld\n", start_num, end_num);

    //register signal
    signal(SIGINT, SIG_DFL);

    //spawn thread to monitor shutdown message
    pthread_attr_t attr;
    pthread_t p_thread_id;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&p_thread_id, &attr, sock_monitor, (void*)&sockfd);

    //take about 15s to handle
    time_t start_time;
    start_time = clocks();
    for (long i = start_num; i < end_num; i++)
    {
        if (check_perfect_number(i) == 0)
        {
            //yeah, perfect num
            memset(buf, 0, sizeof(buf));
            sprintf(buf, ",%ld.", i);
            write(sockfd, buf, strlen(buf));
        }
    }
    PRINTFF("take time: %ld\n", (clocks() - start_time)/1800000000);
    write(sockfd, "end", 3);
    struct timespec ts1 = {
       .tv_sec = 0,
       .tv_nsec = 10000
    };
    nanosleep(&ts1, NULL);
	// close the socket
	close(sockfd);

    return 0;
}
