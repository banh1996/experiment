#include <netdb.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define TESTER_PRESENT_CYCLE 3.5
#define MAX_MTU 1000
#define IP_SERVER   "10.42.0.146"
#define PORT 13400
#define DELIM_STR   '\n'

/**************************** DEFINE DOIP ****************************/
#define HEADER_LENGTH                12
#define TESTER_ADDR_DEVICE           0x0E00
#define VEHICLE_ADDR_DEVICE          0x0001
#define ACTIVATION_REQ_TYPE          0x0005
#define DIAG_MESS_TYPE               0x8001


#define ROUTING_SUCCESS_CODE         0x10
#define SESSION_CONTROL_REQ          0x1003
/**************************** END DEFINE DOIP ************************/
static int g_verbose = 0;

static void memcpy_reverse(char *dst,
                           char *src,
                           uint32_t len)
{
    for (uint32_t i = 0; i < len; i++)
        dst[i] = src[len - i -1];
}

static void construct_doip_header(char *doip_buf,
                                  uint32_t *doip_buf_len,
                                  uint16_t type)
{
    *doip_buf_len = 0;
    doip_buf[0] = 0x02; /* protocol version ISO 13400-2:2012 */
    doip_buf[1] = 0xfd; /* inverse version */
    *doip_buf_len += 2;

    memcpy_reverse(doip_buf + (*doip_buf_len), (char*)&type, sizeof(type)); /* set type header */
    *doip_buf_len += sizeof(type);
}

static void construct_doip_packet(char *doip_buf,
                                  uint32_t *doip_buf_len,
                                  uint16_t tester_addr,
                                  uint16_t vehicle_addr,
                                  char *packet_buf,
                                  uint32_t packet_length)
{
    uint32_t temp_packet_length;
    temp_packet_length = packet_length + sizeof(tester_addr) + sizeof(vehicle_addr);
    memcpy_reverse(doip_buf + (*doip_buf_len), (char*)&temp_packet_length, sizeof(temp_packet_length)); /* set length of packet */
    *doip_buf_len += sizeof(temp_packet_length);

    memcpy_reverse(doip_buf + (*doip_buf_len), (char*)&tester_addr, sizeof(tester_addr)); /* set tester addr */
    *doip_buf_len += sizeof(tester_addr);

    memcpy_reverse(doip_buf + (*doip_buf_len), (char*)&vehicle_addr, sizeof(vehicle_addr)); /* set vehicle addr */
    *doip_buf_len += sizeof(vehicle_addr);

    memcpy(doip_buf + (*doip_buf_len), packet_buf, packet_length); /* set data*/
    *doip_buf_len += packet_length;
}

#if 0
static uint8_t check_valid_packet(char *doip_buf, uint32_t len)
{
    if ((doip_buf[HEADER_LENGTH] & 0x0f) == 0x0f)
        return 1;
    return 0;
}
#endif

static void wait_packet_in_number(int sockfd, uint32_t packet_expect_count)
{
    uint32_t packet_count = 0;
    int len = 0;
    uint8_t recv_buff[MAX_MTU];
    while (packet_count < packet_expect_count)
    {
        memset(recv_buff, 0, sizeof(recv_buff));
        len = read(sockfd, recv_buff, MAX_MTU);
if (g_verbose) {
        printf("receive %d bytes: ", len);
        for (int i = 0; i < len; i++)
            printf("%x ", recv_buff[i]);
        printf("\n");
}
        if (recv_buff[len-1] == 0xaa)
            packet_count++;
    }
}

static int g_sockfd;
static void timer_handler()
{
    char data[64];
    char send_buff[MAX_MTU+20];
    uint32_t len = 0;

    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    data[0] = 0x3E; data[1] = 0x80;
    construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
    construct_doip_packet(send_buff, &len,
                          TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                          data, 2);
    write(g_sockfd, send_buff, len);
}

static int start_tester_present(double seconds)
{
    struct itimerval it_val;
    double integer, fractional;

    integer = (int)seconds;
    fractional = seconds - integer;

    it_val.it_value.tv_sec = integer;
    it_val.it_value.tv_usec = fractional * 1000000;
    it_val.it_interval = it_val.it_value;

    if (setitimer(ITIMER_REAL, &it_val, NULL) == -1)
        return -1;

    return 0;
}

static int activate_process(int sockfd)
{
    char send_buff[MAX_MTU+20];
    char recv_buff[MAX_MTU+20];
    char data[MAX_MTU];
	uint32_t len = 0;

    /* send request activation DoIp */
    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    construct_doip_header(send_buff, &len, ACTIVATION_REQ_TYPE);
    construct_doip_packet(send_buff, &len,
                          TESTER_ADDR_DEVICE, 0,
                          data, 3);
    write(sockfd, send_buff, len);
    /* receive respond activation DoIp */
    memset(recv_buff, 0, sizeof(recv_buff));
    read(sockfd, recv_buff, HEADER_LENGTH + 5);
    if (!(recv_buff[HEADER_LENGTH] & ROUTING_SUCCESS_CODE))
        return -1;

    /* send request session control */
    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    data[0] = 0x10; data[1] = 0x03;
    construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
    construct_doip_packet(send_buff, &len,
                          TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                          data, 2);
    write(sockfd, send_buff, len);
    /* receive respond session control */
    memset(recv_buff, 0, sizeof(recv_buff));
    len = read(sockfd, recv_buff, MAX_MTU);

    return 0;
}

static void print_help(void)
{
    fprintf(stdout, "help: show help\n"
                    "reset au: request reset Aurix\n"
                    "reset xa: request reset Xavier\n"
                    "recovery on: turn on recovery mode in Xavier\n"
                    "recovery off: turn off recovery mode in Xavier\n"
                    "debug: show log\n"
                    "no debug: not show log\n"
                    "exit: quit program\n\n");
}


int main(int argc, char **argv)
{
    int sockfd;
	struct sockaddr_in servaddr;
    char input[64];
    char data[MAX_MTU];
    char send_buff[MAX_MTU+20];
    //char recv_buff[MAX_MTU+20];
	uint32_t len = 0;

	// socket create and varification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	g_sockfd = sockfd;
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

    if (activate_process(sockfd))
    {
        printf("\nActive failed\n");
        return -1;
    }
    else
        printf("\nActive successful.\n");

    if (signal(SIGALRM, (void(*)(int))timer_handler) == SIG_ERR)
    {
        perror("Unable to catch SIGALRM");
        exit(1);
    }
    start_tester_present(TESTER_PRESENT_CYCLE);

    print_help();

    while (fgets(input, sizeof(input), stdin))
    {
        if (memcmp(input, "reset au", 8) == 0)
        {
            memset(send_buff, 0, sizeof(send_buff));
            memset(data, 0, sizeof(data));
            data[0] = 0x11; data[1] = 0x01;
            construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
            construct_doip_packet(send_buff, &len,
                                  TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                                  data, 2);
            write(sockfd, send_buff, len);
            wait_packet_in_number(sockfd, 1);
            printf("Command successful.\n");
        }
        else if (memcmp(input, "reset xa", 8) == 0)
        {
            memset(send_buff, 0, sizeof(send_buff));
            memset(data, 0, sizeof(data));
            data[0] = 0x31; data[1] = 0x01; data[2] = 0xBE; data[3] = 0xEF; data[4] = 0x00; data[5] = 0x02;
            construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
            construct_doip_packet(send_buff, &len,
                                  TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                                  data, 6);
            write(sockfd, send_buff, len);
            wait_packet_in_number(sockfd, 1);
            printf("Command successful.\n");
        }
        else if (memcmp(input, "recovery", 8) == 0)
        {
            memset(send_buff, 0, sizeof(send_buff));
            memset(data, 0, sizeof(data));
            data[0] = 0x31; data[1] = 0x01; data[2] = 0xBE; data[3] = 0xEF; data[4] = 0x00;
            if (memcmp(input, "recovery on", 11) == 0)
                data[5] = 0x00;
            else if (memcmp(input, "recovery off", 12) == 0)
                data[5] = 0x01;
            construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
            construct_doip_packet(send_buff, &len,
                                  TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                                  data, 6);
            write(sockfd, send_buff, len);
            wait_packet_in_number(sockfd, 1);
            printf("Command successful.\n");
        }
        else if (memcmp(input, "help", 4) == 0)
        {
            print_help();
        }
        else if (memcmp(input, "debug", 5) == 0)
        {
            g_verbose = 1;
        }
        else if (memcmp(input, "no debug", 8) == 0)
        {
            g_verbose = 0;
        }
        else if (memcmp(input, "exit", 4) == 0)
        {
            break;
        }
    }


    // close the socket
    close(sockfd);
    //exit(EXIT_SUCCESS);

    return 0;
}
