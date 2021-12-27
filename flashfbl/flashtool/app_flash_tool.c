#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MAX_MTU 4093
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

typedef struct bin_file_t
{
    uint32_t start_addr;
    uint32_t mem_size;
    char *data;
} bin_file_t;

typedef struct node_memmap_t {
    struct bin_file_t *page;
    struct node_memmap_t *next;
} node_memmap_t;

static bool connection(int * sockfd, bool reconnect)
{
    /* connet socket to server (TC397 board) */
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(IP_SERVER);
    servaddr.sin_port = htons(PORT);
    bool retval = false;

    if(*sockfd)
    {
        if(reconnect)
        {
            // established new reconnection to server
            shutdown(*sockfd,  SHUT_WR);
            close(*sockfd);
            *sockfd = socket(AF_INET, SOCK_STREAM, 0);
            if (*sockfd != -1) {
                retval = true;
            }
        }
        if (connect(*sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
            printf("connection with the server failed...\n");
            retval = false;
        }
        else
        {
            printf("connected to the server...\n");
            retval = true;
        }
    }
    else
    {
        // no socket available
        printf("no socket available...\n");
    }
    return retval;
}

static void str2hex(char *text, uint32_t text_len, char *hex)
{
    for (uint32_t i = 0; i < (text_len / 2); i++)
        sscanf(text + 2*i, "%02hhx", hex + i);
}

static uint32_t hex2int(char *hex, uint32_t count)
{
    uint32_t val = 0, c = 0;
    while (*hex && c < count)
    {
        uint8_t byte = *hex++;
        if (byte >= '0' && byte <= '9')
            byte = byte - '0';
        else if (byte >= 'a' && byte <='f')
            byte = byte - 'a' + 10;
        else if (byte >= 'A' && byte <='F')
            byte = byte - 'A' + 10;
        val = (val << 4) | (byte & 0xF);
        c++;
    }
    return val;
}

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

static bool check_valid_packet(char *doip_buf, uint32_t len)
{
    bool retval = true;
    if ((doip_buf[HEADER_LENGTH] & 0x0f) == 0x0f)
        retval = false;
    return retval;
}

static void wait_packet_in_number(int sockfd, uint32_t packet_expect_count)
{
    uint32_t packet_count = 0, len;
    char recv_buff[MAX_MTU+13];
    while (packet_count < packet_expect_count)
    {
        memset(recv_buff, 0, sizeof(recv_buff));
        len = read(sockfd, recv_buff, MAX_MTU);
        if (check_valid_packet(recv_buff, len))
            packet_count++;
    }
}

static bool wait_programing_respond_packet(int * sockfd)
{
    printf("wait_programing_respond_packet sockptr\r\n");
    uint32_t len;
    uint32_t max_count = 10;
    char recv_buff[MAX_MTU+13];
    clock_t startpoint = clock();
    bool retval = false;

    /* listen for programing session respond (50 02) for 15s */
    while(clock() - startpoint < 15000)
    {
        memset(recv_buff, 0, sizeof(recv_buff));
        len = read(*sockfd, recv_buff, MAX_MTU);
        if (check_valid_packet(recv_buff, len) && len != 0)
        {
            if( ((int)recv_buff[12] == 80) && ((int)recv_buff[13] == 2))
            {
                printf("Respond Programing Session OK! \r\n");
                retval = true;
                break;
            }
        }
    }

    return retval;
}

static uint32_t extract_file_transfer(char *file_name, node_memmap_t *memmap_head)
{
    int fd = open(file_name, O_RDONLY);
    char buf[128];
    uint32_t indexCurrentSymbol = 0;
    int read_bytes;
    int line_read = 0;
    int file_read = 0;
    uint8_t is_set_low_addr = 0;
    uint32_t total_mem_size = 0;
    node_memmap_t *temp_memmap_node = NULL;

    printf("Opened %s\n", file_name);
    if (fd == -1)
    {
        printf("Can not open this file");
        exit(1);
    }

    memset(memmap_head, 0, sizeof(node_memmap_t));
    while (file_read == 0)
    {
        read_bytes = read(fd, &buf[indexCurrentSymbol], 1);
        if (read_bytes == -1)
        {
            perror("read while: -1");
            break;
        }

        if (read_bytes == 0)
        {
            file_read = 1;
        }

        if (buf[indexCurrentSymbol] == DELIM_STR)
        {
            uint32_t data_len = hex2int(&buf[1], 2);
            if (memcmp(buf + 7, "04", 2) == 0) /* case extend linear address type */
            {
                /* more page */
                if (temp_memmap_node == NULL)
                    temp_memmap_node = memmap_head;
                else
                {
                    temp_memmap_node->next = malloc(sizeof(node_memmap_t));
                    memset(temp_memmap_node->next, 0, sizeof (node_memmap_t));
                    temp_memmap_node = temp_memmap_node->next;
                }
                temp_memmap_node->page = malloc(sizeof(bin_file_t));
                memset(temp_memmap_node->page, 0, sizeof (bin_file_t));
                temp_memmap_node->page->start_addr = ((hex2int(buf + 9, 4)) << 16) & 0xFFFF0000;
                is_set_low_addr = 1;
            }
            else if (memcmp(buf + 7, "00", 2) == 0) /* case data type */
            {
                if (is_set_low_addr) /* just below type 04, set low start address */
                {
                    temp_memmap_node->page->start_addr |= ((hex2int(buf + 3, 4)) & 0x0000FFFF);
                    temp_memmap_node->page->data = malloc(MAX_MTU);
                    is_set_low_addr = 0;
                }

                uint32_t temp_memaddr = ((hex2int(buf + 3, 4)) & 0x0000FFFF);
                if ((data_len + temp_memaddr - (temp_memmap_node->page->start_addr & 0x0000FFFF)) >= MAX_MTU)
                {
                    /* MTU full, more page, then save data */
                    temp_memmap_node->next = malloc(sizeof(node_memmap_t));
                    memset(temp_memmap_node->next, 0, sizeof (node_memmap_t));
                    temp_memmap_node->next->page = malloc(sizeof(bin_file_t));
                    memset(temp_memmap_node->next->page, 0, sizeof (bin_file_t));
                    temp_memmap_node->next->page->start_addr = (temp_memmap_node->page->start_addr & 0xFFFF0000);
                    temp_memmap_node->next->page->start_addr |= ((hex2int(buf + 3, 4)) & 0x0000FFFF);
                    temp_memmap_node = temp_memmap_node->next;
                    temp_memmap_node->page->data = malloc(MAX_MTU);
                }

                /* save data into page */
                str2hex(&buf[9], data_len*2, &temp_memmap_node->page->data[temp_memmap_node->page->mem_size]);
                temp_memmap_node->page->mem_size += data_len;
                total_mem_size += data_len;
            }
            else if (memcmp(buf + 7, "01", 2) == 0) /* case end of file */
                break;

            indexCurrentSymbol = 0;
            line_read++;
        }
        else
        {
            indexCurrentSymbol++;
        }
    }
    close(fd);

    return total_mem_size;
}

static uint32_t get_signature(char *file_name, char *sign_data)
{
    int fd = open(file_name, O_RDONLY);
    int indexCurrentSymbol = 0, file_read = 0;
    int read_bytes;
    char buf[512];
    char *separator = " ,\0";
    char *temp_str = NULL;
    uint32_t count = 0;
    if (fd == -1)
        return 0xffffffff;
    while (file_read == 0)
    {
        read_bytes = read(fd, &buf[indexCurrentSymbol], 1);
        if (read_bytes == -1)
        {
            printf("read while: -1\n");
            break;
        }

        if (read_bytes == 0)
        {
            printf("read done\n");
            file_read = 1;
        }

        if (buf[indexCurrentSymbol] == DELIM_STR)
        {
            temp_str = strtok(buf, separator);
            while (temp_str)
            {
                sign_data[count] = hex2int(&temp_str[2], 2);
                temp_str = strtok(NULL, separator);
                count++;
            }
            indexCurrentSymbol = 0;
            break;
        }
        else
        {
            indexCurrentSymbol++;
        }
    }
    close(fd);
    return count;
}

static int flash_process(int *sockfdptr, int sockfd, node_memmap_t *driver_mem_head, node_memmap_t *appl_mem_head,
                                     uint32_t total_driver_mem_size, int32_t total_appl_mem_size,
                                     char *driver_sign_file, char *appl_sign_file)
{
    printf("Flash Process...\n");
    char send_buff[MAX_MTU+20];
    char recv_buff[MAX_MTU+20];
    char data[MAX_MTU];
    char identify_key[28] = "112233445566778899112233445\0";
    uint32_t len = 0;
    uint32_t block_count = 1;
    node_memmap_t *temp_mem_node = NULL;

    printf("send request session control \n");

    /* send request activation DoIp */
    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    construct_doip_header(send_buff, &len, ACTIVATION_REQ_TYPE);
    construct_doip_packet(send_buff, &len,
                          TESTER_ADDR_DEVICE, 0,
                          data, 3);
    write(*sockfdptr, send_buff, len);
    /* receive respond activation DoIp */
    memset(recv_buff, 0, sizeof(recv_buff));
    read(*sockfdptr, recv_buff, HEADER_LENGTH + 5);
    if (!(recv_buff[HEADER_LENGTH] & ROUTING_SUCCESS_CODE))
        return -1;

    /* send request session control */
    printf("send request session control \n");

    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    data[0] = 0x10; data[1] = 0x03;
    construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
    construct_doip_packet(send_buff, &len,
                          TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                          data, 2);
    write(*sockfdptr, send_buff, len);

    /* receive respond session control */
    printf("receive respond session control \n");

    memset(recv_buff, 0, sizeof(recv_buff));
    read(*sockfdptr, recv_buff, HEADER_LENGTH + 3);
    if (recv_buff[HEADER_LENGTH] != 0)
        return -1;
    memset(recv_buff, 0, sizeof(recv_buff));
    read(*sockfdptr, recv_buff, HEADER_LENGTH + 6);


    /* send request routine control */
    printf("send request routine control \n");

    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    data[0] = 0x31; data[1] = 0x01; data[2] = 0x02; data[3] = 0x03;
    construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
    construct_doip_packet(send_buff, &len,
                          TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                          data, 4);
    write(*sockfdptr, send_buff, len);
    /* receive respond routine control */
    printf("receive respond routine control \n");

    memset(recv_buff, 0, sizeof(recv_buff));
    read(*sockfdptr, recv_buff, HEADER_LENGTH + 5);
    if (recv_buff[HEADER_LENGTH] != 0)
        return -1;
    memset(recv_buff, 0, sizeof(recv_buff));
    read(*sockfdptr, recv_buff, HEADER_LENGTH + 8);


    /* send request programming session */
    printf("Request Programming Sessios, socket: %d \n", *sockfdptr);
    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    data[0] = 0x10; data[1] = 0x02;
    construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
    construct_doip_packet(send_buff, &len,
                          TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                          data, 2);
    write(*sockfdptr, send_buff, len);

    /* receive respond programming session */
    printf("receive respond programming session \n");

    memset(recv_buff, 0, sizeof(recv_buff));
    read(*sockfdptr, recv_buff, HEADER_LENGTH + 3);

    if (recv_buff[HEADER_LENGTH] != 0)
        return -1;


    if(!wait_programing_respond_packet(sockfdptr))
    {
        printf("Try to reconnect \r\n");
        bool reconnect = false;
        clock_t startpoint = clock();
        while ((clock() - startpoint < 3000) && !reconnect)
        {
            reconnect = connection(&sockfd, true);
        }
        if(reconnect)
        {
            /* send request activation DoIp */
            memset(send_buff, 0, sizeof(send_buff));
            memset(data, 0, sizeof(data));
            construct_doip_header(send_buff, &len, ACTIVATION_REQ_TYPE);
            construct_doip_packet(send_buff, &len,
                                  TESTER_ADDR_DEVICE, 0,
                                  data, 3);
            write(*sockfdptr, send_buff, len);
            /* receive respond activation DoIp */
            memset(recv_buff, 0, sizeof(recv_buff));
            read(*sockfdptr, recv_buff, HEADER_LENGTH + 5);
            if (!(recv_buff[HEADER_LENGTH] & ROUTING_SUCCESS_CODE))
                return -1;

            /* resend request programming session */
            printf("Resend Request Programming Sessios, socket: %d \n", *sockfdptr);
            memset(send_buff, 0, sizeof(send_buff));
            memset(data, 0, sizeof(data));
            data[0] = 0x10; data[1] = 0x02;
            construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
            construct_doip_packet(send_buff, &len,
                                  TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                                  data, 2);
            write(*sockfdptr, send_buff, len);

            /* receive respond programming session */
            printf("receive respond programming session \n");

            memset(recv_buff, 0, sizeof(recv_buff));
            read(*sockfdptr, recv_buff, HEADER_LENGTH + 3);

            if (recv_buff[HEADER_LENGTH] != 0)
                return -1;
            memset(recv_buff, 0, sizeof(recv_buff));
            read(sockfd, recv_buff, HEADER_LENGTH + 6);
        }
        else{
            exit(0);
        }
    } 

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////


    /* send request security access phase 1 */
    printf("send request security access phase 1, socket: %d \n", *sockfdptr);

    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    data[0] = 0x27; data[1] = 0x07;
    construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
    construct_doip_packet(send_buff, &len,
                          TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                          data, 2);
    write(*sockfdptr, send_buff, len);

    /* receive respond security access phase 1 */
    printf("receive request security access phase 1\n");

    wait_packet_in_number(sockfd, 1);
    memset(recv_buff, 0, sizeof(recv_buff));
    read(*sockfdptr, recv_buff, HEADER_LENGTH + 6);
    uint32_t seed;
    memcpy_reverse((char*)&seed, &recv_buff[HEADER_LENGTH+2], 4);


    /* send request security access phase 2 */
    printf("send request security access phase 2 \n");

    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    data[0] = 0x27; data[1] = 0x08;
    uint32_t key = 0xFFFFFFFF;
    key = key ^ seed;
    memcpy_reverse(data+2, (char*)&key, 4);
    construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
    construct_doip_packet(send_buff, &len,
                          TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                          data, 6);
    write(*sockfdptr, send_buff, len);
    /* receive respond security access phase 2 */
    printf("receive request security access phase 2 \n");

    wait_packet_in_number(*sockfdptr, 2);


    /* send request write data */
    printf("send request write data \n");

    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    data[0] = 0x2e; data[1] = 0xf1; data[2] = 0x07; data[3] = 0x21; data[4] = 0x07; data[5] = 0x07;// TODO: date
    memcpy(&data[6], identify_key, strlen(identify_key));
    construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
    construct_doip_packet(send_buff, &len,
                          TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                          data, 6 + strlen(identify_key));
    write(*sockfdptr, send_buff, len);
    /* receive respond write data */
    printf("receive respond write data \n");

    wait_packet_in_number(*sockfdptr, 2);


    /* send/receive request transfer FlashDrv file */
    printf("receive respond write data \n");

    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    data[0] = 0x34; data[1] = 0x00; data[2] = 0x44;
    memcpy_reverse(&data[3], (char*)&driver_mem_head->page->start_addr, 4);
    memcpy_reverse(&data[7], (char*)&total_driver_mem_size, 4);
    construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
    construct_doip_packet(send_buff, &len,
                          TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                          data, 11);
    write(*sockfdptr, send_buff, len);
    /* receive respond write data */
    wait_packet_in_number(*sockfdptr, 2);

    printf("receive respond write data \r\n");


    while(driver_mem_head != NULL)
    {
        printf("driver_mem_head != NULL \r\n");
        memset(send_buff, 0, sizeof(send_buff));
        memset(data, 0, sizeof(data));
        data[0] = 0x36; data[1] = block_count;
        memcpy(&data[2], driver_mem_head->page->data, driver_mem_head->page->mem_size);
        construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
        construct_doip_packet(send_buff, &len,
                              TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                              data, 2 + driver_mem_head->page->mem_size);
        write(*sockfdptr, send_buff, len);
        /* receive respond write data */
        wait_packet_in_number(*sockfdptr, 2);

        /* next packet */
        temp_mem_node = driver_mem_head;
        driver_mem_head = driver_mem_head->next;
        free(temp_mem_node->page->data);
        free(temp_mem_node->page);
        free(temp_mem_node);
        block_count++;
    }


    /* send request transfer exit */
    printf("send request transfer exit \r\n");

    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    data[0] = 0x37;
    construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
    construct_doip_packet(send_buff, &len,
                          TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                          data, 1);
    write(*sockfdptr, send_buff, len);
    /* receive respond transfer exit */
    printf("receive respond transfer exit \r\n");

    wait_packet_in_number(*sockfdptr, 2);


    /* send request routine control & driver signature*/
    printf("send request routine control & driver signature \r\n");

    uint32_t sign_len = 0;
    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    data[0] = 0x31; data[1] = 0x01; data[2] = 0x02; data[3] = 0x02;
    sign_len = get_signature(driver_sign_file, &data[4]);
    construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
    construct_doip_packet(send_buff, &len,
                          TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                          data, 4 + sign_len);
    write(*sockfdptr, send_buff, len);
    /* receive respond routine control & driver signature*/
    printf("receive respond routine control & driver signature \r\n");

    wait_packet_in_number(*sockfdptr, 2);


    /* send request routine control & check dependency*/
    printf("send request routine control & check dependency \r\n");

    sign_len = 0;
    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    data[0] = 0x31; data[1] = 0x01; data[2] = 0xff; data[3] = 0x00;
    str2hex("44a00a800000557f80", 18, &data[4]);
    construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
    construct_doip_packet(send_buff, &len,
                          TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                          data, 4 + 18/2);
    write(*sockfdptr, send_buff, len);
    /* receive respond routine control & check dependency*/
    printf("Erasing ...\n");
    wait_packet_in_number(*sockfdptr, 2);


    /* send/receive transfer data Appl file */
    temp_mem_node = NULL;
    block_count = 1;
    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    data[0] = 0x34; data[1] = 0x00; data[2] = 0x44;
    memcpy_reverse(&data[3], (char*)&appl_mem_head->page->start_addr, 4);
    //memcpy_reverse(&data[7], (char*)&total_mem_size, 4);
    str2hex("00557f80", 8, &data[7]);
    construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
    construct_doip_packet(send_buff, &len,
                          TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                          data, 11);
    write(*sockfdptr, send_buff, len);
    /* receive respond write data */
    wait_packet_in_number(*sockfdptr, 2);
    uint8_t percent = 0;
    uint32_t sent_size = 0;
    printf("Flashing %d%%", percent);
    while(appl_mem_head != NULL)
    {
        memset(send_buff, 0, sizeof(send_buff));
        memset(data, 0, sizeof(data));
        data[0] = 0x36; data[1] = block_count;
        memcpy(&data[2], appl_mem_head->page->data, appl_mem_head->page->mem_size);
        construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
        construct_doip_packet(send_buff, &len,
                              TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                              data, 2 + appl_mem_head->page->mem_size);
        write(*sockfdptr, send_buff, len);

        /* receive respond write data */
        wait_packet_in_number(*sockfdptr, 2);
        /* print current download */
        sent_size += appl_mem_head->page->mem_size;
        percent = sent_size*100/total_appl_mem_size;
        printf("\rFlashing %02d%%", percent);

        /* next packet */
        temp_mem_node = appl_mem_head;
        appl_mem_head = appl_mem_head->next;
        free(temp_mem_node->page->data);
        free(temp_mem_node->page);
        free(temp_mem_node);
        block_count++;
    }


    /* send request transfer exit */
    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    data[0] = 0x37;
    construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
    construct_doip_packet(send_buff, &len,
                          TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                          data, 1);
    write(*sockfdptr, send_buff, len);
    /* receive respond transfer exit */
    wait_packet_in_number(*sockfdptr, 2);


    /* send request routine control & appl signature*/
    sign_len = 0;
    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    data[0] = 0x31; data[1] = 0x01; data[2] = 0x02; data[3] = 0x02;

    sign_len = get_signature(appl_sign_file, &data[4]);
    construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
    construct_doip_packet(send_buff, &len,
                          TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                          data, 4 + sign_len);
    write(*sockfdptr, send_buff, len);
    /* receive respond routine control & appl signature*/
    wait_packet_in_number(*sockfdptr, 2);


    /* send request routine control*/
    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    data[0] = 0x31; data[1] = 0x01; data[2] = 0xff; data[3] = 0x01;

    construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
    construct_doip_packet(send_buff, &len,
                          TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                          data, 4);
    write(*sockfdptr, send_buff, len);
    /* receive respond routine control & driver signature*/
    wait_packet_in_number(*sockfdptr, 2);

    printf("\nFlash successful.\n");
    return 0;
}




int main(int argc, char **argv)
{
    int sockfd;
    char driver_hex_file[13] = "FlashDrv.hex\0";
    char appl_hex_file[21] = "AdasSafetyMcuBEV.hex\0";
    char driver_sign_file[18] = "FlashDrv_hmac.sig\0";
    char appl_sign_file[26] = "AdasSafetyMcuBEV_hmac.sig\0";

    //extract driver and app hex file
    node_memmap_t *appl_mem_head = malloc(sizeof(node_memmap_t));
    node_memmap_t *driver_mem_head = malloc(sizeof(node_memmap_t));
    uint32_t total_appl_mem_size, total_driver_mem_size;

    memset(appl_mem_head, 0, sizeof (node_memmap_t));
    total_appl_mem_size = extract_file_transfer(appl_hex_file, appl_mem_head);

    memset(driver_mem_head, 0, sizeof (node_memmap_t));
    total_driver_mem_size = extract_file_transfer(driver_hex_file, driver_mem_head);

    // socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("creat socket unsuccessfully\n");
        exit(0);
    }
    else
        printf("Socket successfully created...\n");

    // assign IP, PORT

    connection(&sockfd, false);

    // connect the client socket to server socket


    if (argc == 2)
    {
        if (memcmp(argv[1], "ICE", 3) == 0)
        {
            sprintf(appl_hex_file, "AdasSafetyMcuICE.hex");
            sprintf(appl_sign_file, "AdasSafetyMcuICE_hmac.sig");
        }
    }

    // function for flashing
    flash_process(&sockfd, sockfd,
                  driver_mem_head, appl_mem_head,
                  total_driver_mem_size, total_appl_mem_size,
                  driver_sign_file, appl_sign_file);

    // close the socket
    close(sockfd);

    return 0;
}