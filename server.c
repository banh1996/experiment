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

struct sockaddr_in address; 
socklen_t addrlen = sizeof(address);
static int server_fd; 
static uint16_t port = 0;
static uint32_t max_client = 0;
static uint32_t current_client = 0;
static char ip[20];
static char folder_path[100];

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

    if (listen(server_fd, 0) < 0) 
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
		close(sourse_fd);
        close(skt);
		return false;
	}

	printf("sending file from: %s\n", filename);

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
    int new_conn = *(int*)argv;
    int n = 0;
    char file_request[100];

    if(pthread_detach(pthread_self()))
	{
        current_client--;
		perror("pthread detach error ");
        pthread_exit(NULL);
	}

	printf("Thread %ld has started\n", pthread_self());

    memset(file_request, 0, sizeof(file_request));
    memcpy(file_request, folder_path, strlen(folder_path));
	n = read(new_conn, &file_request[strlen(file_request)], sizeof(file_request) - strlen(file_request));

    printf("read request file: %s\n", file_request);

    if(access(file_request, F_OK) != -1 )
    {
        printf("File %s existed\n", file_request);
        write(new_conn, "ok", 2);
    }
    else
    {
        printf("File %s is not exist\n", file_request);
        write(new_conn, "no", 2);
        current_client--;
        pthread_exit(NULL);
    }

    send_text_file_data(new_conn, file_request);
	
	printf("Thread %ld has finished\n", pthread_self());
    current_client--;
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

    init_socket();

    while(true)
    {
        pthread_t id_thread;
        if(current_client >= max_client)
            continue;
        current_client++;
        int new_conn = accept_new_connection();
        if (pthread_create(&id_thread, NULL, threadFunc, &new_conn) != 0)
        {
            printf("Thread created error\n");
        }
    }

    return 1;
}