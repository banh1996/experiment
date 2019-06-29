#include <stdio.h> 
#include <stdbool.h>
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <errno.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h> 
#include <pthread.h>

#define SOCKET_TYPE	AF_INET
#define BUFFER_SIZE	1024
#define FILE_OUTPUT	"out.bin"
#define MAX_THREAD  10

typedef struct
{
	char name[50];
}small_file_t;
static small_file_t	smallFileName[MAX_THREAD];
static pthread_t    tid[MAX_THREAD];
static uint16_t port = 0;
static char ip[20];
static int num_thread = 0;
pthread_mutex_t 			mutex = PTHREAD_MUTEX_INITIALIZER;

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

static bool get_info_socket(const char *file_name)
{
    char str[5];
    memset(ip, 0, sizeof(ip));
    memset(str, 0, sizeof(str));
    FILE * file;
    file = fopen(file_name, "r");
    if (file) 
    {
        fscanf(file, "%s", ip);
        printf("ip: %s\n",ip);

        fscanf(file, "%s", str);
        port = atoi(str);
        printf("port: %d\n", port);

        fclose(file);
        return true;
    }
    else
    {
        printf("cannot find config file\n");
        return false;
    }
}

static int init_socket(void)
{
    int sock = 0;
    struct sockaddr_in serv_addr; 
    if ((sock = socket(SOCKET_TYPE, SOCK_STREAM, 0)) < 0) 
    { 
        perror("Socket creation error"); 
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr)); 
    serv_addr.sin_family = SOCKET_TYPE; 
    serv_addr.sin_port = htons(port); 

    if(inet_pton(SOCKET_TYPE, ip, &serv_addr.sin_addr) <= 0)  
    { 
        perror("Invalid address/ Address not supported"); 
        return -1;
    } 

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        perror("Connection Failed"); 
        return -1;
    }
    return sock;
}

static void save_file_receive_from_server(int client_sockfd, char *filename_save)
{
	char buf[BUFFER_SIZE];

    int read_len, des_fd, addr_len;
	struct sockaddr_in server_add;

    /* create file */
    des_fd = open(filename_save, O_WRONLY  | O_CREAT | O_TRUNC, 0777);

    if(des_fd == -1) 
    {
        perror("file open error : ");
    } 

    printf("Saving file %s\n", filename_save);
    
    /* file save */
    while(1) 
    {
        read_len = read(client_sockfd, buf, BUFFER_SIZE);
        
        if(read_len <= 0) 
        {
            printf("finish saved file\n");
            break;
        }
		write(des_fd, buf, read_len);
    }
    close(des_fd);
}

void *threadFunc(void *argv)
{
	int  new_conn = 0;
	char buf[BUFFER_SIZE];

	printf("Thread %ld has started\n", pthread_self());

	pthread_mutex_lock(&mutex);
	new_conn = init_socket();
	pthread_mutex_unlock(&mutex);

    memset(buf, 0x00, BUFFER_SIZE);
	sprintf(buf, "start");
	int n = write(new_conn, buf, 6);
	memset(buf, 0x00, BUFFER_SIZE);
	n = read(new_conn, buf, BUFFER_SIZE);
	int num = atoi(buf);
	sprintf(smallFileName[num].name, "out%d", num);
    write(new_conn, "ok\0", 3);
	save_file_receive_from_server(new_conn, smallFileName[num].name);

	printf("Thread %ld has finished\n", pthread_self());
	close(new_conn);
	pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    bool b_result = false;

    b_result = get_info_socket("config.cfg");
    if(!b_result)
        return 0;
    
    int new_conn = 0, n;
    char buf[100];
    new_conn = init_socket();
    if(new_conn < 0)
        return 0;
    if (argc > 2)
    {
        n = write(new_conn, argv[2],strlen(argv[2]));
    }

    while(true)
	{
		memset(buf, 0x00, sizeof(buf));
		n = read(new_conn, buf, BUFFER_SIZE);
		if(n > 0)
		{
			if(atoi(buf))
			{
		  		printf("Receive from server: %s\n", buf);
				n = write(new_conn, "ok\0", 3);
				break;
			}
		}
		else
        {
            perror("no receive ok");
            return 0;
        }
	}
	num_thread = atoi(buf);
	printf("num thread %d\n", num_thread);
    sleep(1);

    for(int i = 0; i < num_thread; i++)
	{
		memset(smallFileName[i].name, 0, 50);
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
}