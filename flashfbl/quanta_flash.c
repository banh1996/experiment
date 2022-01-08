/* ********************************************************************************************************************

 *

 * COPYRIGHT RESERVED, 2021 VinFast Trading and Production LLC. All rights reserved.

 * The reproduction, distribution and utilization of this document as well as the communication of its contents to

 * others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.

 * All rights reserved in the event of the grant of a patent, utility model or design.

 *

 ******************************************************************************************************************* */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
// #include <sys/time.h>
// #include <signal.h>
//#include "hmac1.h"

#define DEBUG_LOG printf

#define MAX_MTU 4093
#define IP_SERVER   "10.42.0.146"
#define PORT 13400
#define DELIM_STR   '\n'

#define DATALEN_PER_LINE             32
#define FIRST_LEN                    3
#define LOW_DATA_LEN                 4
#define HEXCODE_LEN                  2
#define HIGH_DATA_LEN                4
#define CRC_LEN                      2
#define DELIM_LEN                    2

/**************************** DEFINE DOIP ****************************/
#define HEADER_LENGTH                12
#define TESTER_ADDR_DEVICE           0x0E00
#define VEHICLE_ADDR_DEVICE          0x0001
#define ACTIVATION_REQ_TYPE          0x0005
#define DIAG_MESS_TYPE               0x8001


#define ROUTING_SUCCESS_CODE         0x10
#define SESSION_CONTROL_REQ          0x1003
/**************************** END DEFINE DOIP ************************/
#define TESTER_PRESENT_CYCLE 3.5
/************************* DEFINE STRUCT-ENUM ************************/
typedef struct bin_file_t
{
    uint32_t cur_addr;
    uint32_t mem_size;
    char *data;
} bin_file_t;


typedef enum FOTA_state_t {
    FOTA_ERROR = 0,
    FOTA_NOTHING,
    FOTA_IN_PROGRESS,
} FOTA_state_t;
/*********************** END DEFINE STRUCT-ENUM **********************/

static int change_fota_state(char *file_name, char *state_str)
{
    int filefd;

    filefd = open(file_name, O_RDWR | O_TRUNC | O_CREAT);

    if (filefd == -1)
    {
        DEBUG_LOG("Can not open file %s", file_name);
        return -1;
    }
    DEBUG_LOG("Opened %s file\n", file_name);

    write(filefd, state_str, strlen(state_str));
    close(filefd);
    return 0;
}

static int connection(int sockfd)
{
    /* connet socket to server (TC397 board) */
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(IP_SERVER);
    servaddr.sin_port = htons(PORT);

    if(sockfd)
    {
        if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
            DEBUG_LOG("connection with the server failed...\n");
            return -1;
        }
        else
        {
            DEBUG_LOG("connected to the server...\n");
            return 0;
        }
    }
    else
    {
        // no socket available
        DEBUG_LOG("no socket available...\n");
    }
    return -1;
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

static int check_valid_packet(char *doip_buf, uint32_t len)
{
    if ((doip_buf[HEADER_LENGTH] & 0x0f) == 0x0f)
        return -1;
    return 0;
}

static void wait_packet_in_number(int sockfd, uint32_t packet_expect_count)
{
    uint32_t packet_count = 0, len;
    char recv_buff[MAX_MTU+13];
    while (packet_count < packet_expect_count)
    {
        memset(recv_buff, 0, sizeof(recv_buff));
        len = read(sockfd, recv_buff, MAX_MTU);
        if (check_valid_packet(recv_buff, len) == 0)
            packet_count++;
    }
}

static int wait_programing_respond_packet(int sockfd)
{
    DEBUG_LOG("wait_programing_respond_packet sockptr\r\n");
    uint32_t len;
    uint32_t max_count = 10;
    char recv_buff[MAX_MTU+13];
    //clock_t startpoint = clock();

    /* listen for programing session respond (50 02) for 15s */
    //while(clock() - startpoint < 15000)
    while(1)
    {
        memset(recv_buff, 0, sizeof(recv_buff));
        len = read(sockfd, recv_buff, MAX_MTU);
        if (check_valid_packet(recv_buff, len) && len != 0)
        {
            if( ((int)recv_buff[12] == 80) && ((int)recv_buff[13] == 2))
            {
                DEBUG_LOG("Respond Programing Session OK! \r\n");
                return 0;
                //break;
            }
        }
    }

    return -1;
}

static uint32_t extract_file_transfer(int sockfd, char *file_name)
{
    int filefd;
    char buf[128];
    uint32_t indexCurrentSymbol = 0;
    int read_bytes;
    int line_read = 0;
    int file_read = 0;
    uint8_t is_extend_linear_type = 0;
    uint32_t total_mem_size = 0;
    uint32_t current_address = 0;
    uint32_t expand_size = 0;
    uint32_t line_data_len = 0;
    bin_file_t *temp_page = NULL;

    uint8_t block_count = 1;
    char send_buff[MAX_MTU+20];
    char recv_buff[MAX_MTU+20];
    char data[MAX_MTU];
    uint8_t percent = 0;
    uint32_t sent_size = 0;
    uint32_t len = 0;
    uint32_t total_appl_mem_size = 0x00557f80;

    filefd = open(file_name, O_RDONLY);
    if (filefd == -1)
        exit(1);
    DEBUG_LOG("Opened %s\n", file_name);
    memset(buf, 0, sizeof(buf));
    while (file_read == 0)
    {
        read_bytes = read(filefd, &buf[indexCurrentSymbol], FIRST_LEN);
        if (read_bytes == -1)
        {
            DEBUG_LOG("read while: -1\n");
            break;
        }
        else if (read_bytes == 0)
        {
            DEBUG_LOG("read done\n");
            file_read = 1;
        }
        indexCurrentSymbol += FIRST_LEN;
        line_data_len = hex2int(&buf[1], 2); //get data len per line
        read_bytes = read(filefd, &buf[indexCurrentSymbol], LOW_DATA_LEN+HEXCODE_LEN+line_data_len*2+CRC_LEN+DELIM_LEN);
        if (read_bytes == -1)
        {
            DEBUG_LOG("read done\n");
            break;
        }
        else if (read_bytes == 0)
        {
            DEBUG_LOG("read done\n");
            file_read = 1;
        }
        indexCurrentSymbol += LOW_DATA_LEN+HEXCODE_LEN+line_data_len*2+CRC_LEN+DELIM_LEN;

        /* check hex code */
        if (memcmp(buf+FIRST_LEN+LOW_DATA_LEN, "04", 2) == 0) /* case extend linear address type */
        {
            /* init page */
            if (temp_page == NULL)
            {
                temp_page = malloc(sizeof(bin_file_t));
                memset(temp_page, 0, sizeof (bin_file_t));
                temp_page->data = malloc(MAX_MTU);
            }
            temp_page->cur_addr = ((hex2int(buf+FIRST_LEN+LOW_DATA_LEN+HEXCODE_LEN, HIGH_DATA_LEN)) << 16) & 0xFFFF0000;

            if (temp_page->cur_addr == 0xAF400000)
            {
                memset(send_buff, 0, sizeof(send_buff));
                memset(data, 0, sizeof(data));
                data[0] = 0x36; data[1] = block_count;
                memcpy(&data[2], temp_page->data, temp_page->mem_size);
                construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
                construct_doip_packet(send_buff, &len,
                                    TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                                    data, 2 + temp_page->mem_size);
                write(sockfd, send_buff, len);

                /* receive respond write data */
                wait_packet_in_number(sockfd, 2);
                /* print current download */
                sent_size += temp_page->mem_size;
                percent = sent_size*100/total_appl_mem_size;
                DEBUG_LOG("\rFlashing %02d%%", percent);

                /* free memory */
                free(temp_page->data);
                free(temp_page);
                temp_page = NULL;
                block_count++;
                break;
            }
        }
        else if (memcmp(buf+FIRST_LEN+LOW_DATA_LEN, "00", 2) == 0) /* case read data type */
        {
            uint32_t lowmemaddr = ((hex2int(buf+FIRST_LEN, LOW_DATA_LEN)) & 0x0000FFFF);
            temp_page->cur_addr &= 0xFFFF0000;
            temp_page->cur_addr |= lowmemaddr;
            // DEBUG_LOG("current addr1 %x %x %d\n", current_address, temp_page->cur_addr, temp_page->mem_size);

            /* check if need to expand */
            if (current_address != 0 && current_address < temp_page->cur_addr)
            {
                /* expand 0 */
                uint32_t page_expand_size = 0;
                expand_size = temp_page->cur_addr - current_address;
                //DEBUG_LOG("expand %d to %x\n", expand_size, temp_page->cur_addr);
                while (expand_size > 0)
                {
                    if (expand_size <= MAX_MTU - temp_page->mem_size)
                    {
                        page_expand_size = expand_size;
                        memset(&temp_page->data[temp_page->mem_size], 0, page_expand_size);
                        temp_page->mem_size += page_expand_size;
                        current_address += page_expand_size;
                        temp_page->cur_addr = current_address;
                    }
                    else
                    {
                        page_expand_size = MAX_MTU - temp_page->mem_size;
                        memset(&temp_page->data[temp_page->mem_size], 0, page_expand_size);
                        temp_page->mem_size += page_expand_size;
                        current_address += page_expand_size;
                        /* TODO: send data via socket here */
                        if (temp_page != NULL)
                        {
                            memset(send_buff, 0, sizeof(send_buff));
                            memset(data, 0, sizeof(data));
                            data[0] = 0x36; data[1] = block_count;
                            memcpy(&data[2], temp_page->data, temp_page->mem_size);
                            construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
                            construct_doip_packet(send_buff, &len,
                                                TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                                                data, 2 + temp_page->mem_size);
                            write(sockfd, send_buff, len);

                            /* receive respond write data */
                            wait_packet_in_number(sockfd, 2);
                            /* print current download */
                            sent_size += temp_page->mem_size;
                            percent = sent_size*100/total_appl_mem_size;
                            DEBUG_LOG("\rFlashing %02d%%", percent);

                            /* free memory */
                            free(temp_page->data);
                            free(temp_page);
                            temp_page = NULL;
                            block_count++;
                        }
                        /* MTU full, more page */
                        temp_page = malloc(sizeof(bin_file_t));
                        memset(temp_page, 0, sizeof (bin_file_t));
                        temp_page->cur_addr = current_address;
                        temp_page->data = malloc(MAX_MTU);
                    }
                    expand_size -= page_expand_size;
                }
            }
            current_address = temp_page->cur_addr;
            current_address += line_data_len;
            // DEBUG_LOG("current addr2 %x %x %d\n", current_address, temp_page->cur_addr, temp_page->mem_size);
            if ((line_data_len + temp_page->mem_size) >= MAX_MTU)
            {
                uint32_t temp_saveaddr = temp_page->cur_addr;
                /* TODO send data flash via socket here */
                if (temp_page != NULL)
                {
                    memset(send_buff, 0, sizeof(send_buff));
                    memset(data, 0, sizeof(data));
                    data[0] = 0x36; data[1] = block_count;
                    memcpy(&data[2], temp_page->data, temp_page->mem_size);
                    construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
                    construct_doip_packet(send_buff, &len,
                                        TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                                        data, 2 + temp_page->mem_size);
                    write(sockfd, send_buff, len);

                    /* receive respond write data */
                    wait_packet_in_number(sockfd, 2);
                    /* print current download */
                    sent_size += temp_page->mem_size;
                    percent = sent_size*100/total_appl_mem_size;
                    DEBUG_LOG("\rFlashing %02d%%", percent);

                    /* free memory */
                    free(temp_page->data);
                    free(temp_page);
                    temp_page = NULL;
                    block_count++;
                }

                /* MTU full, more page, then save data */
                temp_page = malloc(sizeof(bin_file_t));
                memset(temp_page, 0, sizeof (bin_file_t));
                temp_page->cur_addr = (temp_saveaddr & 0xFFFF0000);
                temp_page->cur_addr |= ((hex2int(buf+FIRST_LEN, LOW_DATA_LEN)) & 0x0000FFFF);
                temp_page->data = malloc(MAX_MTU);
            }

            /* save data into page */
            str2hex(buf+FIRST_LEN+LOW_DATA_LEN+HEXCODE_LEN, line_data_len*2, &temp_page->data[temp_page->mem_size]);
            temp_page->mem_size += line_data_len;
            total_mem_size += line_data_len;
        }
        else if (memcmp(buf+FIRST_LEN+LOW_DATA_LEN, "01", 2) == 0) /* case end of file */
        {
            /* TODO send data flash via socket here */
            if (temp_page != NULL)
            {
                memset(send_buff, 0, sizeof(send_buff));
                memset(data, 0, sizeof(data));
                data[0] = 0x36; data[1] = block_count;
                memcpy(&data[2], temp_page->data, temp_page->mem_size);
                construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
                construct_doip_packet(send_buff, &len,
                                    TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                                    data, 2 + temp_page->mem_size);
                write(sockfd, send_buff, len);

                /* receive respond write data */
                wait_packet_in_number(sockfd, 2);
                /* print current download */
                sent_size += temp_page->mem_size;
                percent = sent_size*100/total_appl_mem_size;
                DEBUG_LOG("\rFlashing %02d%%", percent);

                /* free memory */
                free(temp_page->data);
                free(temp_page);
                temp_page = NULL;
                block_count++;
            }
            break;
        }

        indexCurrentSymbol = 0;
        line_read++;
    }
    close(filefd);

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
            DEBUG_LOG("read while: -1\n");
            break;
        }

        if (read_bytes == 0)
        {
            DEBUG_LOG("read done\n");
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

static int request_appl_switch_fbl(int sockfd)
{
    char send_buff[MAX_MTU+20];
    char recv_buff[MAX_MTU+20];
    char data[MAX_MTU];
    uint32_t len = 0;

    DEBUG_LOG("send request session control \n");

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
    DEBUG_LOG("send request session control \n");

    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    data[0] = 0x10; data[1] = 0x03;
    construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
    construct_doip_packet(send_buff, &len,
                          TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                          data, 2);
    write(sockfd, send_buff, len);

    /* receive respond session control */
    DEBUG_LOG("receive respond session control \n");

    memset(recv_buff, 0, sizeof(recv_buff));
    read(sockfd, recv_buff, HEADER_LENGTH + 3);
    if (recv_buff[HEADER_LENGTH] != 0)
        return -1;
    memset(recv_buff, 0, sizeof(recv_buff));
    read(sockfd, recv_buff, HEADER_LENGTH + 6);


    /* send request routine control */
    DEBUG_LOG("send request routine control \n");

    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    data[0] = 0x31; data[1] = 0x01; data[2] = 0x02; data[3] = 0x03;
    construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
    construct_doip_packet(send_buff, &len,
                          TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                          data, 4);
    write(sockfd, send_buff, len);
    /* receive respond routine control */
    DEBUG_LOG("receive respond routine control \n");

    memset(recv_buff, 0, sizeof(recv_buff));
    read(sockfd, recv_buff, HEADER_LENGTH + 5);
    if (recv_buff[HEADER_LENGTH] != 0)
        return -1;
    memset(recv_buff, 0, sizeof(recv_buff));
    read(sockfd, recv_buff, HEADER_LENGTH + 8);


    /* send request programming session */
    DEBUG_LOG("Request Programming Sessios, socket: %d \n", sockfd);
    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    data[0] = 0x10; data[1] = 0x02;
    construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
    construct_doip_packet(send_buff, &len,
                          TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                          data, 2);
    write(sockfd, send_buff, len);

    /* receive respond programming session */
    DEBUG_LOG("receive respond programming session \n");

    memset(recv_buff, 0, sizeof(recv_buff));
    read(sockfd, recv_buff, HEADER_LENGTH + 3);

    if (recv_buff[HEADER_LENGTH] != 0)
        return -1;

    if (wait_programing_respond_packet(sockfd) == -1)
        perror("request boot to fbl fail\n");
    return 0;
}

static int flash_process(int sockfd, int is_noapp,
                        char *driver_file, char *appl_file,
                        uint32_t total_driver_mem_size, int32_t total_appl_mem_size,
                        char *driver_sign_file, char *appl_sign_file)
{
    DEBUG_LOG("Flash Process...\n");
    char send_buff[MAX_MTU+20];
    char recv_buff[MAX_MTU+20];
    char data[MAX_MTU];
    char finger_print[28] = "112233445566778899112233445\0";
    uint32_t len = 0;
    uint32_t block_count = 1;

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

    if (is_noapp)
    {
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
        read(sockfd, recv_buff, HEADER_LENGTH + 3);
        if (recv_buff[HEADER_LENGTH] != 0)
            return -1;
        memset(recv_buff, 0, sizeof(recv_buff));
        read(sockfd, recv_buff, HEADER_LENGTH + 6);


        /* send request routine control */
        memset(send_buff, 0, sizeof(send_buff));
        memset(data, 0, sizeof(data));
        data[0] = 0x31; data[1] = 0x01; data[2] = 0x02; data[3] = 0x03;
        construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
        construct_doip_packet(send_buff, &len,
                            TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                            data, 4);
        write(sockfd, send_buff, len);
        /* receive respond routine control */
        memset(recv_buff, 0, sizeof(recv_buff));
        read(sockfd, recv_buff, HEADER_LENGTH + 5);
        if (recv_buff[HEADER_LENGTH] != 0)
            return -1;
        memset(recv_buff, 0, sizeof(recv_buff));
        read(sockfd, recv_buff, HEADER_LENGTH + 8);
    }

    /* send request programming session */
    DEBUG_LOG("Resend Request Programming Sessios, socket: %d \n", sockfd);
    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    data[0] = 0x10; data[1] = 0x02;
    construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
    construct_doip_packet(send_buff, &len,
                            TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                            data, 2);
    write(sockfd, send_buff, len);
    /* receive respond programming session */
    DEBUG_LOG("receive respond programming session \n");
    memset(recv_buff, 0, sizeof(recv_buff));
    read(sockfd, recv_buff, HEADER_LENGTH + 3);
    if (recv_buff[HEADER_LENGTH] != 0)
        return -1;
    memset(recv_buff, 0, sizeof(recv_buff));
    read(sockfd, recv_buff, HEADER_LENGTH + 6);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////


    /* send request security access phase 1 */
    DEBUG_LOG("send request security access phase 1, socket: %d \n", sockfd);
    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    data[0] = 0x27; data[1] = 0x07;
    construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
    construct_doip_packet(send_buff, &len,
                          TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                          data, 2);
    write(sockfd, send_buff, len);
    /* receive respond security access phase 1 */
    DEBUG_LOG("receive request security access phase 1\n");
    wait_packet_in_number(sockfd, 1);
    memset(recv_buff, 0, sizeof(recv_buff));
    read(sockfd, recv_buff, HEADER_LENGTH + 6);
    uint32_t seed;
    memcpy_reverse((char*)&seed, &recv_buff[HEADER_LENGTH+2], 4);
    uint8_t hash_key[16] = {0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t hash_data[16];
    uint8_t hash_out[20];
    //memcpy(hash_data, &recv_buff[HEADER_LENGTH+2], 16);


    /* send request security access phase 2 */
    DEBUG_LOG("send request security access phase 2 \n");
    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    data[0] = 0x27; data[1] = 0x08;
    uint32_t key = 0xFFFFFFFF;
    key = key ^ seed;
    //HMACSHA1(hash_key, hash_data, hash_out);
    //memcpy(data+2, hash_out, 16);
    memcpy(data+2, (char*)&key, 4);
    construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
    construct_doip_packet(send_buff, &len,
                          TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                          data, 6);
    write(sockfd, send_buff, len);
    /* receive respond security access phase 2 */
    DEBUG_LOG("receive request security access phase 2 \n");
    wait_packet_in_number(sockfd, 2);


    /* send request write data */
    DEBUG_LOG("send request write data \n");
    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    data[0] = 0x2e; data[1] = 0xf1; data[2] = 0x07; data[3] = 0x21; data[4] = 0x07; data[5] = 0x07;// TODO: date
    memcpy(&data[6], finger_print, strlen(finger_print));
    construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
    construct_doip_packet(send_buff, &len,
                          TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                          data, 6 + strlen(finger_print));
    write(sockfd, send_buff, len);
    /* receive respond write data */
    DEBUG_LOG("receive respond write data \n");
    wait_packet_in_number(sockfd, 2);


    /* send/receive request transfer FlashDrv file */
    DEBUG_LOG("receive respond write data \n");

    uint32_t driver_startaddr = 0x70100200;
    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    data[0] = 0x34; data[1] = 0x00; data[2] = 0x44;
    memcpy_reverse(&data[3], (char*)&driver_startaddr, 4);
    memcpy_reverse(&data[7], (char*)&total_driver_mem_size, 4);
    construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
    construct_doip_packet(send_buff, &len,
                          TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                          data, 11);
    write(sockfd, send_buff, len);
    /* receive respond write data */
    wait_packet_in_number(sockfd, 2);

    DEBUG_LOG("receive respond write data \r\n");


    /* flash driver */
    extract_file_transfer(sockfd, driver_file);


    /* send request transfer exit */
    DEBUG_LOG("send request transfer exit \r\n");

    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    data[0] = 0x37;
    construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
    construct_doip_packet(send_buff, &len,
                          TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                          data, 1);
    write(sockfd, send_buff, len);
    /* receive respond transfer exit */
    DEBUG_LOG("receive respond transfer exit \r\n");

    wait_packet_in_number(sockfd, 2);


    /* send request routine control & driver signature*/
    DEBUG_LOG("send request routine control & driver signature \r\n");

    uint32_t sign_len = 0;
    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    data[0] = 0x31; data[1] = 0x01; data[2] = 0x02; data[3] = 0x02;
    sign_len = get_signature(driver_sign_file, &data[4]);
    construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
    construct_doip_packet(send_buff, &len,
                          TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                          data, 4 + sign_len);
    write(sockfd, send_buff, len);
    /* receive respond routine control & driver signature*/
    DEBUG_LOG("receive respond routine control & driver signature \r\n");

    wait_packet_in_number(sockfd, 2);


    /* send request routine control & check dependency*/
    DEBUG_LOG("send request routine control & check dependency \r\n");

    sign_len = 0;
    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    data[0] = 0x31; data[1] = 0x01; data[2] = 0xff; data[3] = 0x00;
    str2hex("44a00a800000557f80", 18, &data[4]);
    construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
    construct_doip_packet(send_buff, &len,
                          TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                          data, 4 + 18/2);
    write(sockfd, send_buff, len);
    /* receive respond routine control & check dependency*/
    DEBUG_LOG("Erasing ...\n");
    wait_packet_in_number(sockfd, 2);


    /* send/receive transfer data Appl file */
    uint32_t appl_startaddr = 0xa00a8000;
    block_count = 1;
    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    data[0] = 0x34; data[1] = 0x00; data[2] = 0x44;
    memcpy_reverse(&data[3], (char*)&appl_startaddr, 4);
    //memcpy_reverse(&data[7], (char*)&total_mem_size, 4);
    str2hex("00557f80", 8, &data[7]);
    construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
    construct_doip_packet(send_buff, &len,
                          TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                          data, 11);
    write(sockfd, send_buff, len);
    /* receive respond write data */
    wait_packet_in_number(sockfd, 2);
    uint8_t percent = 0;
    uint32_t sent_size = 0;
    //DEBUG_LOG("Flashing %d%%", percent);
    /* flash appl */
    extract_file_transfer(sockfd, appl_file);


    /* send request transfer exit */
    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    data[0] = 0x37;
    construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
    construct_doip_packet(send_buff, &len,
                          TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                          data, 1);
    write(sockfd, send_buff, len);
    /* receive respond transfer exit */
    wait_packet_in_number(sockfd, 2);


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
    write(sockfd, send_buff, len);
    /* receive respond routine control & appl signature*/
    wait_packet_in_number(sockfd, 2);

    change_fota_state("/samples/systems/fota_aurix/result.txt\0", "flashok\n\0");
    DEBUG_LOG("\nFlash successful.\n");

    /* send request routine control*/
    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    data[0] = 0x31; data[1] = 0x01; data[2] = 0xff; data[3] = 0x01;

    construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
    construct_doip_packet(send_buff, &len,
                          TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                          data, 4);
    write(sockfd, send_buff, len);
    /* receive respond routine control & driver signature*/
    wait_packet_in_number(sockfd, 2);

    /* send reset */
    memset(send_buff, 0, sizeof(send_buff));
    memset(data, 0, sizeof(data));
    data[0] = 0x10; data[1] = 0x01;
    construct_doip_header(send_buff, &len, DIAG_MESS_TYPE);
    construct_doip_packet(send_buff, &len,
                          TESTER_ADDR_DEVICE, VEHICLE_ADDR_DEVICE,
                          data, 2);
    write(sockfd, send_buff, len);
    /* receive respond routine control & driver signature*/
    wait_packet_in_number(sockfd, 2);
    return 0;
}


#if 0
static FOTA_state_t check_fota_state(char *file_name)
{
    int filefd;
    char buf[128];
    uint32_t indexCurrentSymbol = 0;
    int read_bytes;
    int file_read = 0;

    // if( access( file_name, F_OK ) != 0 ) {
    //     // file doesn't exist
    //     return 0;
    // }

    filefd = open(file_name, O_RDWR);

    if (filefd == -1)
    {
        DEBUG_LOG("Can not open file %s", file_name);
        return FOTA_ERROR;
    }
    DEBUG_LOG("Opened %s file\n", file_name);
    while (file_read == 0)
    {
        read_bytes = read(filefd, &buf[indexCurrentSymbol], 1);
        if (read_bytes == -1)
        {
            perror("read while: -1");
            break;
        }

        if (read_bytes == 0)
            file_read = 1;

        if (buf[indexCurrentSymbol] == DELIM_STR)
        {
            if (memcmp(buf, "FOTA_NOTHING", 12) == 0)
                return FOTA_NOTHING;
            else if (memcmp(buf, "FOTA_IN_PROGRESS", 16) == 0)
                return FOTA_IN_PROGRESS;
            else if (memcmp(buf, "FOTA_ERROR", 10) == 0)
                return FOTA_IN_PROGRESS;
            break;
        }
        else
        {
            indexCurrentSymbol++;
        }
    }

    return FOTA_ERROR;
}
#endif

#if 0
static int g_sockfd;
static void timer_handler(void)
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
#endif

int main(int argc, char **argv)
{
    int sockfd;
    char driver_hex_file[128] = "FlashDrv.hex\0";
    char appl_hex_file[128] = "AdasSafetyMcuBEV.hex\0";
    char driver_sign_file[128] = "FlashDrv_hmac.sig\0";
    char appl_sign_file[128] = "AdasSafetyMcuBEV_hmac.sig\0";
    char fota_state_file[128] = "fotastate.txt\0";
    char temp_str[128];

#if 0
    //check FOTA state
    FOTA_state_t fota_state = check_fota_state(fota_state_file);
    if (fota_state == FOTA_ERROR)
        exit(-1);
    else if (fota_state == FOTA_NOTHING)
    {
        DEBUG_LOG("wait for MHU instructions\n");
        // while(1)
        // ;
    }
#endif
    if (argc == 1)
    {
        change_fota_state("/samples/systems/fota_aurix/fotastate.txt\0", "FOTA_IN_PROGRESS\0");
    }

    sleep(5);

    // socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    //g_sockfd = sockfd;
    if (sockfd == -1) {
        DEBUG_LOG("creat socket unsuccessfully\n");
        exit(0);
    }
    else
        DEBUG_LOG("Socket successfully created...\n");

    // connect the client socket to server socket
    if (connection(sockfd) == -1)
        exit(-1);


    // if (signal(SIGALRM, (void(*)(int))timer_handler) == SIG_ERR)
    // {
    //     perror("Unable to catch SIGALRM");
    //     exit(1);
    // }
    // start_tester_present(TESTER_PRESENT_CYCLE);

    if (argc == 1)
    {
        //change_fota_state("/samples/systems/fota_aurix/fotastate.txt\0", "FOTA_IN_PROGRESS\0");
        //sleep(2);
        request_appl_switch_fbl(sockfd);
        /* wait for reseting */
        exit(0);
    }
    else if (argc < 3)
    {
        printf("not enough arguments\n");
        exit(-1);
    }
    //continue FOTA sequence

    uint32_t total_appl_mem_size = 0x00557f80, total_driver_mem_size = 1292;

    memset(temp_str, 0, sizeof(temp_str));
    sprintf(temp_str, "%s", argv[2]);
    sprintf(&temp_str[strlen(temp_str)], "%s", driver_hex_file);
    sprintf(driver_hex_file, "%s\0", temp_str);

    memset(temp_str, 0, sizeof(temp_str));
    sprintf(temp_str, "%s", argv[2]);
    sprintf(&temp_str[strlen(temp_str)], "%s", appl_hex_file);
    sprintf(appl_hex_file, "%s\0", temp_str);

    memset(temp_str, 0, sizeof(temp_str));
    sprintf(temp_str, "%s", argv[2]);
    sprintf(&temp_str[strlen(temp_str)], "%s", driver_sign_file);
    sprintf(driver_sign_file, "%s\0", temp_str);

    memset(temp_str, 0, sizeof(temp_str));
    sprintf(temp_str, "%s", argv[2]);
    sprintf(&temp_str[strlen(temp_str)], "%s", appl_sign_file);
    sprintf(appl_sign_file, "%s\0", temp_str);

    memset(temp_str, 0, sizeof(temp_str));
    sprintf(temp_str, "%s", argv[2]);
    sprintf(&temp_str[strlen(temp_str)], "%s", fota_state_file);
    sprintf(fota_state_file, "%s\0", temp_str);

    DEBUG_LOG("fota file %s\n", fota_state_file);
    change_fota_state(fota_state_file, "FOTA_NOTHING\0");

    if (memcmp(argv[1], "noapp", 5) == 0)
    {
        // function for flashing
        flash_process(sockfd, 1,
                      driver_hex_file, appl_hex_file,
                      total_driver_mem_size, total_appl_mem_size,
                      driver_sign_file, appl_sign_file);
    }
    else if (memcmp(argv[1], "continue", 8) == 0)
    {
        // function for flashing
        flash_process(sockfd, 0,
                      driver_hex_file, appl_hex_file,
                      total_driver_mem_size, total_appl_mem_size,
                      driver_sign_file, appl_sign_file);
    }

    // close the socket
    close(sockfd);

    return 0;
}