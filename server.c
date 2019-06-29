#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>

#define AF_FAMILY 	AF_INET
#define BUFFER_SIZE 1024
#define PORT     	8080 
#define FILENAME 	"in.bin"
#define NUM_THREAD	20
#define FILE_SIZE   FileSize(FILENAME)

typedef struct
{
	char name[50];
}small_file_t;

static pthread_t    		tid[NUM_THREAD];
static small_file_t			smallFileName[NUM_THREAD];
static uint16_t				g_current_port = PORT;
pthread_mutex_t 			mutex = PTHREAD_MUTEX_INITIALIZER;

/*function to get size of the file.*/
size_t FileSize(const char *file_name)
{
    struct stat st;
    if(stat(file_name,&st)==0)
        return (st.st_size);
    else
        return -1;
}

static void init_socket_udp(int *soc_fd, uint16_t temp_port)
{
	/*Create a UDP server socket*/
	*soc_fd = socket(AF_FAMILY, SOCK_DGRAM, 0);
	if(*soc_fd == -1)
	{
		perror("Create socket fail !\n");
		exit(EXIT_FAILURE); 
	}
	else
		printf("Create socket successful %d %d\n", *soc_fd, temp_port);
	/*Server address*/
	struct sockaddr_in server_add;
	bzero(&server_add, sizeof(server_add));
	server_add.sin_family = AF_FAMILY;
	server_add.sin_port = htons(temp_port);
	server_add.sin_addr.s_addr = htonl(INADDR_ANY);
	/*Bind server socket to address*/
	if(bind(*soc_fd, (struct sockaddr *)&server_add, sizeof(server_add))== -1)
	{
		perror("Bind fail");
		exit(EXIT_FAILURE); 
	}
	else
		printf("Bind successful\n");
}

static void split_file(const char *filename)
{
    int segments = 0, i, accum, readfile_len = 1;
    int fp1, fp2;
    size_t sizeFile = FileSize(FILENAME);
	size_t smallsizefile = sizeFile/NUM_THREAD;
    segments = NUM_THREAD + 1;//ensure end of file
    
    char line[BUFFER_SIZE];

    fp1 = open(filename, O_RDONLY);
    if(fp1)
    {
        for(i = 0; i < segments; i++)
        {
            accum = 0;
            sprintf(smallFileName[i].name, "%s%d", filename, i);
            fp2 = open(smallFileName[i].name, O_WRONLY  | O_CREAT | O_TRUNC, 0777);
            if(fp2)
            {
                while(readfile_len && accum <= smallsizefile)
                {
					readfile_len = read(fp1, line, BUFFER_SIZE);
                    accum += readfile_len;//track size of growing file
                    write(fp2, line, readfile_len);
                }
                close(fp2);
            }
        }
        close(fp1);
    }
}

static bool send_text_file_data(int skt, const char *filename,
								struct sockaddr_in client_add, int addr_len)
{
	char buf[BUFFER_SIZE];
  	int send_len, read_len, sourse_fd;
	printf("name send: %s %s %d %d\n", filename, inet_ntoa(client_add.sin_addr), ntohs(client_add.sin_port), addr_len);
	if(sendto(skt, filename, strlen(filename), MSG_CONFIRM, (struct sockaddr*)&client_add, addr_len) < 0)
	{
		perror("Error send name: ");
		return false;
	}
	sourse_fd = open(filename, O_RDONLY);
	if(sourse_fd == -1)
	{
		memset(buf, 0x00, BUFFER_SIZE);
		sprintf(buf, "no found file %s", filename);
		printf("%s\n", buf);
		if(sendto(skt, buf, strlen(buf), MSG_CONFIRM,  (struct sockaddr*)&client_add, addr_len) < 0)
			perror("Error send: ");
		close(sourse_fd);
		return false;
	}

	printf("sending file: %s\n", filename);
	//int cnt = 0;
	while(1) 
	{
		//cnt++;
		memset(buf, 0x00, BUFFER_SIZE);
		read_len = read(sourse_fd, buf, BUFFER_SIZE);
		send_len = sendto(skt, buf, read_len, MSG_CONFIRM,  (struct sockaddr*)&client_add, addr_len);
		//printf("here: %d %d %d\n", read_len, send_len, cnt);
		usleep(4);
		if(send_len <= 0 || read_len <=0) 
		{
			break;
		}
	}
	close(sourse_fd);
	return true;
}

void *threadFunc(void *argv)
{
	int sock_fd, n;
	socklen_t len_recv = sizeof(struct sockaddr_in);
	char buf[BUFFER_SIZE];
	pthread_mutex_lock(&mutex);
	g_current_port++;
	init_socket_udp(&sock_fd, g_current_port);
	pthread_mutex_unlock(&mutex);

	if(pthread_detach(pthread_self()))
	{
		printf("pthread detach error\n");
	}
	printf("Thread %ld has started\n", pthread_self());
	struct sockaddr_in client_add;
	memset(buf, 0x00, BUFFER_SIZE);
	n = recvfrom(sock_fd, buf, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr*)&client_add, &len_recv);
	if(n > 0)
	{
		if(memcmp(buf, "start", 5) == 0)
		{
			usleep(100);
			send_text_file_data(sock_fd, (char*)(argv), client_add, sizeof(client_add));
		}
		else
		{
			printf("wrong key\n");
		}
	}
	else
	{
		perror("no no no\n");
	}
	
	printf("Thread %ld has finished\n", pthread_self());
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	bool continu = false;
	int ret = 0, i = 0, n, sock_fd;
	socklen_t len_recv = sizeof(struct sockaddr_in);
	struct sockaddr_in client_add;
	char buf[BUFFER_SIZE];
	
	if ((argc > 1) && (atoi(argv[1]) > 0))
	{
		g_current_port = atoi(argv[1]);
		init_socket_udp(&sock_fd, g_current_port);
	}
	else
		init_socket_udp(&sock_fd, PORT);
    split_file(FILENAME);

    bzero(&client_add, sizeof(client_add));
	
	memset(buf, 0, BUFFER_SIZE);
    n = recvfrom(sock_fd, buf, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr*)&client_add, &len_recv);
    if(n > 0)
    {
    	printf("From address: %s\n", inet_ntoa(client_add.sin_addr));
	  	printf("From Port: %d\n",ntohs(client_add.sin_port));
	  	printf("Receive from client: %s\n", buf);
	}
    else
		perror("no receive anything");

	memset(buf, 0, BUFFER_SIZE);
	sprintf(buf, "%d", NUM_THREAD);

	//send thread num back
	while(true)
	{
		if(sendto(sock_fd, buf, strlen(buf) + 1, MSG_CONFIRM,  (struct sockaddr*)&client_add, sizeof(client_add)) < 0)
			perror("Error send: ");

		//wait client reply
		memset(buf, 0, BUFFER_SIZE);
		n = recvfrom(sock_fd, buf, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr*)&client_add, &len_recv);
		if(n > 0)
		{
			if(memcmp(buf, "ok", 2) == 0)
			{
				printf("ok\n");
				break;
			}
		}
		else
			perror("no receive ok\n");
	}

	for(i = 0; i < NUM_THREAD; i++)
	{
		memset(smallFileName[i].name, 0, BUFFER_SIZE);
		sprintf(smallFileName[i].name, "%s%d", FILENAME, i);
		ret = pthread_create(&(tid[i]), NULL, threadFunc, (void*)smallFileName[i].name);
		if (ret != 0)
		{
			printf("Thread [%d] created error\n", i);
		}
	}

	/*Wait for receive from client*/
	while(!continu)
	{
	  /*Send file to client*/
	//   if(!send_text_file_data(serverfd, FILENAME))
	//   {
	// 	  printf("Closed socket\n");
	// 	  close(serverfd); 
	// 	  continu = false;
	//   }
	}
	return 0;
}
