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

#define SOCKET_TYPE	AF_INET
#define BUFFER_SIZE	1024
#define FILE_OUTPUT	"out.bin"

static uint16_t port = 0;
static char ip[20];

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


int main(int argc, char const *argv[])
{
    char file_name[100];
    char buf[100];
    int new_conn = 0;

    if(!get_info_socket("config.cfg"))
        return 0;
    
    new_conn = init_socket();
    if(new_conn < 0)
        return 0;
    
    memset(file_name, 0, sizeof(file_name));
    if (argc > 2)
    {
        memcpy(file_name, argv[2], strlen(argv[2]));
        write(new_conn, argv[2], strlen(argv[2]));
    }
    else
    {
        printf("no enough argument\n");
        return 0;
    }
    
    memset(buf, 0, sizeof(buf));
    int n = read(new_conn, buf, 2);
    printf("buf: %s %d\n", buf, n);
    if(memcmp(buf, "ok", 2))
    {
        printf("no find file %s\n", file_name);
        return 0;
    }
    
    save_file_receive_from_server(new_conn, file_name);
    close(new_conn);
}