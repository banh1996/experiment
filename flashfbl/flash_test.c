#include <netdb.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define MAX_MTU 1280
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


/**************************** DEFINE STRUCT ****************************/
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
/**************************** END DEFINE STRUCT ***********************/


/**************************** LOCAL VARIABLE ****************************/

/**************************** END LOCAL VARIABLE ************************/


static void str2hex(char *text, uint32_t text_len, char *hex)
{
    for (uint32_t i = 0; i < (text_len / 2); i++)
        sscanf(text + 2*i, "%02x", hex + i);
}

static void memcpy_reverse(char *dst,
                           char *src,
                           uint32_t len)
{
    for (uint32_t i = 0; i < len; i++)
        dst[i] = src[len - i -1];
}

uint32_t hex2int(char *hex, uint32_t count) {
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
        exit(1);

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
printf("line %d\n", __LINE__);
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
//printf("line %d %x %x\n", __LINE__, temp_memaddr, temp_memmap_node->page->start_addr & 0x0000FFFF);
                if ((data_len + temp_memaddr - (temp_memmap_node->page->start_addr & 0x0000FFFF)) >= MAX_MTU)
                {
                    /* MTU full, more page, then save data */
printf("line %d %d\n", __LINE__, sizeof(node_memmap_t));
                    temp_memmap_node->next = malloc(sizeof(node_memmap_t));
                    memset(temp_memmap_node->next, 0, sizeof (node_memmap_t));
printf("line %d\n", __LINE__);
                    temp_memmap_node->next->page = malloc(sizeof(bin_file_t));
                    memset(temp_memmap_node->next->page, 0, sizeof (bin_file_t));
                    temp_memmap_node->next->page->start_addr = (temp_memmap_node->page->start_addr & 0xFFFF0000);
                    temp_memmap_node->next->page->start_addr |= ((hex2int(buf + 3, 4)) & 0x0000FFFF);
                    temp_memmap_node = temp_memmap_node->next;
                    temp_memmap_node->page->data = malloc(MAX_MTU);
                }

                /* save data into page */
printf("line %d %d %d\n", __LINE__, data_len, temp_memmap_node->page->mem_size);
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


int main()
{
    node_memmap_t *mem_head = malloc(sizeof(node_memmap_t));
    memset(mem_head, 0, sizeof (node_memmap_t));
    printf("here %x\n", extract_file_transfer("AdasSafetyMcuBEV.hex", mem_head));

    // while (mem_head != NULL)
    // {
    //     printf("result: %x %x\n", mem_head->page->start_addr, mem_head->page->mem_size);
    //     // for (int i = 0; i < mem_head->page->mem_size; i++)
    //     //     printf("%02x ", mem_head->page->data[i]);
    //     mem_head = mem_head->next;
    // }
}
