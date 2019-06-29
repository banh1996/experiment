#include <unistd.h> 
#include <stdio.h> 
#include <stdbool.h>
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <arpa/inet.h>
#include <pthread.h>

#define SOCKET_TYPE	AF_INET
#define BUFFER_SIZE	1024
#define MAX_THREAD	10

typedef struct
{
	char name[50];
}small_file_t;

static pthread_t    		tid[MAX_THREAD];
static small_file_t			smallFileName[MAX_THREAD];
pthread_mutex_t 			mutex = PTHREAD_MUTEX_INITIALIZER;
struct sockaddr_in address; 
socklen_t addrlen = sizeof(address); 

static int server_fd; 

static uint16_t port = 0;
static uint32_t max_client = 0;
static char ip[20];
static char folder_path[100];
static char file_request[100];

size_t FileSize(const char *file_name)
{
    struct stat st;
    if(stat(file_name,&st)==0)
        return (st.st_size);
    else
        return -1;
}

static void split_file(const char *filename)
{
    int segments = 0, i, accum, readfile_len = 1;
    int fp1, fp2;
    size_t sizeFile = FileSize(filename);
	size_t smallsizefile = sizeFile/max_client;
    segments = max_client + 1;//ensure end of file
    printf("file size: %ld %ld\n", sizeFile, smallsizefile);
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
            else
            {
                perror("file open fp2 error ");
            }
            
        }
        close(fp1);
        printf("split file successfull\n");
    }
    else
    {
        perror("file open fp1 error ");
    }
}

static bool get_info_socket(const char *file_name)
{
    char str[5];
    memset(ip, 0, sizeof(ip));
    memset(str, 0, sizeof(str));
    memset(folder_path, 0, sizeof(folder_path));
    FILE * file;
    file = fopen(file_name, "r");
    if (file) 
    {
        fscanf(file, "%s", ip);
        printf("ip: %s\n",ip);

        fscanf(file, "%s", str);
        port = atoi(str);
        printf("port: %d\n", port);

        memset(str, 0, sizeof(str));
        fscanf(file, "%s", str);
        max_client = atoi(str);
        printf("max client: %d\n", max_client);

        fscanf(file, "%s", folder_path);
        printf("folder path: %s\n", folder_path);
        fclose(file);
        return true;
    }
    else
    {
        printf("cannot find config file\n");
        return false;
    }
}

static void init_socket(void)
{
    int opt = 1; 
    if ((server_fd = socket(SOCKET_TYPE, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    }  

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = SOCKET_TYPE; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) 
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, MAX_THREAD) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
}

static int accept_new_connection(void)
{
    int new_conn = 0;
    if ((new_conn = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen))<0) 
    { 
        perror("accept error"); 
        exit(EXIT_FAILURE); 
    }
    return new_conn;
}

static bool send_text_file_data(int skt, const char *filename)
{
	char buf[BUFFER_SIZE];
  	int send_len, read_len, sourse_fd;
	
	sourse_fd = open(filename, O_RDONLY);
	if(sourse_fd == -1)
	{
		memset(buf, 0x00, BUFFER_SIZE);
		sprintf(buf, "no found file %s", filename);
		printf("%s\n", buf);
		if(write(skt, buf, strlen(buf)) < 0)
			perror("Error send: ");
		close(sourse_fd);
        close(skt);
		return false;
	}

	printf("sending file from: %s\n", filename);
    //usleep(50);
	while(1) 
	{
		memset(buf, 0x00, BUFFER_SIZE);
		read_len = read(sourse_fd, buf, BUFFER_SIZE);
		send_len = write(skt, buf, read_len);
		if(send_len <= 0 || read_len <=0) 
		{
			break;
		}
	}
	close(sourse_fd);
    close(skt);
	return true;
}


void *threadFunc(void *argv)
{
	int n, new_conn;
	char buf[BUFFER_SIZE];

	pthread_mutex_lock(&mutex);
	new_conn = accept_new_connection();
	pthread_mutex_unlock(&mutex);

	if(pthread_detach(pthread_self()))
	{
		perror("pthread detach error ");
	}
	printf("Thread %ld has started\n", pthread_self());

    memset(buf, 0x00, BUFFER_SIZE);
	n = read(new_conn, buf, BUFFER_SIZE);
	if(n > 0)
	{
		if(memcmp(buf, "start", 5) == 0)
		{
            if(write(new_conn, (char*)argv + strlen(file_request), strlen((char*)(argv) + strlen(file_request))) < 0)//send file name
            {
                perror("Error send name");
                pthread_exit(NULL);
            }
            memset(buf, 0x00, BUFFER_SIZE);
            n = read(new_conn, buf, BUFFER_SIZE);
            if(memcmp(buf, "ok", 2) == 0)
            {
                send_text_file_data(new_conn, (char*)(argv));
            }
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

int main(int argc, char const *argv[])
{
    bool b_result = false;
    if (argc > 1)
	{
		b_result = get_info_socket(argv[1]);
	}
    else
    {
        b_result = get_info_socket("config.cfg");
    }
    
    if(!b_result)
        return 0;

    int new_conn = 0, n = 0;
    char buf[100];

    init_socket();
    
    new_conn = accept_new_connection();
    memset(buf, 0, sizeof(buf));
    memset(file_request, 0, sizeof(file_request));
	n = read(new_conn, buf, sizeof(buf));
    memcpy(file_request, buf, n);
    printf("read request file: %s\n", file_request);

    if(access(file_request, F_OK) != -1 )
    {
        printf("File %s existed\n", file_request);
    }
    else
    {
        printf("File %s is not exist\n", file_request);
        return 0;
    }
    split_file(file_request);

    memset(buf, 0, sizeof(buf));
	sprintf(buf, "%d", max_client);
	//send thread num back
	while(true)
	{
		if(write(new_conn, buf, strlen(buf) + 1) < 0)
			perror("Error send: ");

		memset(buf, 0, sizeof(buf));
		n = read(new_conn, buf, sizeof(buf));
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

    for(int i = 0; i < max_client; i++)
	{
		memset(smallFileName[i].name, 0, 50);
		sprintf(smallFileName[i].name, "%s%d", file_request, i);
		if (pthread_create(&(tid[i]), NULL, threadFunc, (void*)smallFileName[i].name) != 0)
		{
			printf("Thread [%d] created error\n", i);
		}
	}

    void *ret_val;
	for(int i = 0; i < max_client; i++)
	{
		pthread_join(tid[i], ret_val);
	}
    printf("DONE\n");
    while(1)
    ;
}