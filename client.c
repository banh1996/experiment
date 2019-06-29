#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>

#define SOCKET_FAMILY	AF_INET
#define BUFFER_SIZE 	1024
#define IP_ADDR			"127.0.0.1"
#define PORT     		8080 
#define FILE_OUTPUT		"out.bin"
#define MAX_THREAD		20

typedef struct
{
	char name[50];
}small_file_t;
static small_file_t	smallFileName[MAX_THREAD];
static pthread_t    tid[MAX_THREAD];
static int 			num_thread = 0;
static uint16_t 	g_server_port = PORT;
pthread_mutex_t 	mutex = PTHREAD_MUTEX_INITIALIZER;

static void merge_file(const char *filename)
{
	printf("Merging files\n");
    int i, readfile_len = 1;
    int fp1, fp2;
    char line[BUFFER_SIZE];

    fp1 = open(filename, O_WRONLY  | O_CREAT | O_TRUNC, 0777);
    if(fp1)
    {
        for(i = 0; i < num_thread; i++)
        {
			readfile_len = 1;
            fp2 = open(smallFileName[i].name, O_RDONLY);
            if(fp2)
            {
                while(readfile_len)
                {
					readfile_len = read(fp2, line, BUFFER_SIZE);
                    write(fp1, line, readfile_len);
                }
                close(fp2);
            }
        }
        close(fp1);
    }
	printf("Done merged files\n");
}

static void init_socket_udp(int *sock_fd)
{
	/*Create a socket*/
	*sock_fd = socket(SOCKET_FAMILY, SOCK_DGRAM, 0);
	if(*sock_fd == -1)
		perror("create socket failed\n");
	else
		printf("create socket successful %d\n", *sock_fd);
}

static void save_file_receive_from_server(int client_sockfd, char *filename)
{
	char buf[BUFFER_SIZE];

    int read_len, des_fd, addr_len;
	struct sockaddr_in server_add;

    /* create file */
    des_fd = open(filename, O_WRONLY  | O_CREAT | O_TRUNC, 0777);

    if(des_fd == -1) 
    {
        perror("file open error : ");
    } 

    printf("Saving file %s\n", filename);
    /* file save */
	//int cnt = 0;
    while(1) 
    {
		//cnt++;
        //memset(buf, 0x00, BUFFER_SIZE);
        read_len = recvfrom(client_sockfd, buf, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr*)&server_add, &addr_len);
        
        if(read_len <= 0) 
        {
            printf("finish saved file\n");
            break;
        }
		write(des_fd, buf, read_len);
		//printf("here: %d %d %d\n", read_len, file_write_len, cnt);
    }
    close(des_fd);
}

void *threadFunc(void *argv)
{
	int n, sock_fd = 0;
	unsigned int len_recv = 0;
	char buf[BUFFER_SIZE];
	struct sockaddr_in server_add;

	memset(buf, 0, BUFFER_SIZE);

	printf("Thread %ld has started\n", pthread_self());
	
	bzero(&server_add, sizeof(server_add));
	server_add.sin_family = SOCKET_FAMILY;

	pthread_mutex_lock(&mutex);
	init_socket_udp(&sock_fd);
	g_server_port++;
	server_add.sin_port = htons(g_server_port);
	pthread_mutex_unlock(&mutex);

	if(inet_pton(SOCKET_FAMILY, IP_ADDR, &server_add.sin_addr)<0)
	{
		perror("fail to convert address\n");
		pthread_exit(NULL);
	}

	memset(buf, 0x00, BUFFER_SIZE);
	sprintf(buf, "start %d", g_server_port);
	n = sendto(sock_fd, buf, 11, MSG_CONFIRM,  (struct sockaddr*)&server_add, sizeof(server_add));
	memset(buf, 0x00, BUFFER_SIZE);
	n = recvfrom(sock_fd, buf, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr*)&server_add, &len_recv);
	char name[10];
	sprintf(name, "out%s", buf + 2);
	save_file_receive_from_server(sock_fd, name);
	printf("Thread %ld has finished\n", pthread_self());
	close(sock_fd);
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	int sock_fd = 0, n;
	socklen_t len_recv = sizeof(struct sockaddr_in);
	struct sockaddr_in server_add;
	char buf[BUFFER_SIZE];

	if ((argc > 1) && (atoi(argv[1]) > 0))
	{
		g_server_port = atoi(argv[1]);
	}
	init_socket_udp(&sock_fd);
	
	/*Get socket address*/
	
	bzero(&server_add, sizeof(server_add));
	server_add.sin_family = SOCKET_FAMILY;
	server_add.sin_port = htons(g_server_port);
	if(inet_pton(SOCKET_FAMILY, IP_ADDR, &server_add.sin_addr)<0)
	{
		perror("fail to convert address\n");
		return(1);
	}

	n = sendto(sock_fd, "hello \0", 7, MSG_CONFIRM,  (struct sockaddr*)&server_add, sizeof(server_add));
	if(n > 0)
		printf("Message send successful\n");
	else
		printf("Message send fail\n");

	while(true)
	{
		memset(buf, 0x00, BUFFER_SIZE);
		n = recvfrom(sock_fd, buf, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr*)&server_add, &len_recv);
		if(n > 0)
		{
			if(atoi(buf))
			{
				printf("From address: %s\n", inet_ntoa(server_add.sin_addr));
	  			printf("From Port: %d\n",ntohs(server_add.sin_port));
		  		printf("Receive from server: %s\n", buf);
				n = sendto(sock_fd, "ok\0", 3, MSG_CONFIRM,  (struct sockaddr*)&server_add, sizeof(server_add));
				break;
			}
		}
		else
			perror("no receive ok");
	}
	num_thread = atoi(buf);
	printf("num thread %d\n", num_thread);
	sleep(1);

	//TODO
	for(int i = 0; i < num_thread; i++)
	{
		memset(smallFileName[i].name, 0, 50);
		sprintf(smallFileName[i].name, "%s%d", FILE_OUTPUT, i);
		int ret = pthread_create(&(tid[i]), NULL, threadFunc, NULL);
		if (ret != 0)
		{
			printf("Thread [%d] created error\n", i);
		}
	}

	void *ret_val;
	for(int i = 0; i < num_thread; i++)
	{
		pthread_join(tid[i], ret_val);
	}
	merge_file(FILE_OUTPUT);

	while(true)
	{
		/*Close the socket*/
		// if(close(sock_fd))
		// {
		// 	printf("Error closing file\n");
		// 	return(1);
		// }
		// else
		// {
		// 	printf("Close successful\n");
		// }
	}
	return 0;
}
