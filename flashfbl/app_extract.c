#include <netdb.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>


#define DELIM_STR   '\n'
#define MAX_MTU     4093

/**************************** DEFINE DOIP ****************************/
#define DATALEN_PER_LINE             32
#define FIRST_LEN                    3
#define LOW_DATA_LEN                 4
#define HEXCODE_LEN                  2
#define HIGH_DATA_LEN                4
#define CRC_LEN                      2
#define DELIM_LEN                    1
/**************************** END DEFINE DOIP ************************/


/**************************** DEFINE STRUCT ****************************/
typedef struct bin_file_t
{
    uint32_t cur_addr;
    uint32_t mem_size;
    char *data;
} bin_file_t;
/**************************** END DEFINE STRUCT ***********************/


/**************************** LOCAL VARIABLE ****************************/

/**************************** END LOCAL VARIABLE ************************/


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
    printf("Opened %s\n", file_name);
    memset(temp_page, 0, sizeof(bin_file_t));
    while (file_read == 0)
    {
        read_bytes = read(filefd, &buf[indexCurrentSymbol], FIRST_LEN);
        if (read_bytes == -1)
        {
            perror("read while: -1");
            break;
        }
        else if (read_bytes == 0)
        {
            file_read = 1;
        }
        indexCurrentSymbol += FIRST_LEN;
        line_data_len = hex2int(&buf[1], 2); //get data len per line
        read_bytes = read(filefd, &buf[indexCurrentSymbol], LOW_DATA_LEN+HEXCODE_LEN+line_data_len*2+CRC_LEN+DELIM_LEN);
        if (read_bytes == -1)
        {
            perror("read while: -1");
            break;
        }
        else if (read_bytes == 0)
        {
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
        }
        else if (memcmp(buf+FIRST_LEN+LOW_DATA_LEN, "00", 2) == 0) /* case read data type */
        {
            uint32_t lowmemaddr = ((hex2int(buf+FIRST_LEN, LOW_DATA_LEN)) & 0x0000FFFF);
            temp_page->cur_addr &= 0xFFFF0000;
            temp_page->cur_addr |= lowmemaddr;

            /* check if need to expand */
            if (current_address != 0 && current_address < temp_page->cur_addr)
            {
                /* expand 0 */
                uint32_t page_expand_size = 0;
                expand_size = temp_page->cur_addr - current_address;
                while (expand_size > 0)
                {
                    if (expand_size <= MAX_MTU - temp_page->mem_size)
                    {
                        page_expand_size = expand_size-temp_page->mem_size;
                        memset(&temp_page->data[temp_page->mem_size], 0, page_expand_size);
                        temp_page->mem_size += page_expand_size;
                        current_address += current_address + page_expand_size;
                    }
                    else
                    {
                        page_expand_size = MAX_MTU-temp_page->mem_size;
                        memset(&temp_page->data[temp_page->mem_size], 0, page_expand_size);
                        temp_page->mem_size += page_expand_size;
                        current_address += current_address + page_expand_size;
                        /* TODO: send data via socket here */
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
            if ((line_data_len + temp_page->mem_size) >= MAX_MTU)
            {
                /* TODO send data flash via socket here */

                /* MTU full, more page, then save data */
                temp_page = malloc(sizeof(bin_file_t));
                memset(temp_page, 0, sizeof (bin_file_t));
                temp_page->cur_addr = (temp_page->cur_addr & 0xFFFF0000);
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
            break;
        }

        indexCurrentSymbol = 0;
        line_read++;
    }
    close(filefd);

    return total_mem_size;
}


int main(int argc, char **argv)
{
    char driver_hex_file[13] = "FlashDrv.hex\0";
    char appl_hex_file[21] = "AdasSafetyMcuBEV.hex\0";
    char driver_sign_file[18] = "FlashDrv_hmac.sig\0";
    char appl_sign_file[26] = "AdasSafetyMcuBEV_hmac.sig\0";

    uint32_t total_appl_mem_size = extract_file_transfer(appl_hex_file);

    uint32_t total_driver_mem_size = extract_file_transfer(driver_hex_file);


    return 0;
}
