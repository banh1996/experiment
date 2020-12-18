#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define BUF_LEN  50

typedef struct node_t
{
    char *p_data;
    struct node_t *next;
} node_t;

// static char input[BUF_LEN] = {1, 0, 1, 0, 1, 1, 1, 0, 0, 0};
// static char input[BUF_LEN] = {1, 1, 0, 1, 1, 0, 0, 0};
// static char input[BUF_LEN] = {1, 1, 0, 0};
static char input[BUF_LEN] = {'1', '1', '0', '0', '1', '1', '1', '0', '0', '0', '1', '1', '1', '1', '0', '0', '1', '0', '0', '0'};

static int compare_substrings(char *a1, char *a2)
{
    int len;
    if (strlen(a1) > strlen(a2))
        return 0;
    else if (strlen(a1) < strlen(a2))
        return 1;
    len = strlen(a1);
    for (int i = 0; i < len; i++)
    {   
        if (a1[i] > a2[i])
            return 0;
        if (a1[i] < a2[i])
            return 1;
    }   
    return 0;
}

static node_t *find_substring(char *a)
{
    int count0 = 0, count1 = 0, index = 0, len = strlen(a);
    node_t *p_node = NULL, *temp_p_node = NULL;
    p_node = malloc(sizeof(node_t*));
    temp_p_node = p_node;
    for (int i = 0; i < len; i++)
    {
        if (a[i] == '1')
        {
            count1++;
        }
        else
        {
            count0++;
        }

        if (count1 == count0)
        {
            count1 = 0;
            count0 = 0;
            p_node->p_data = malloc((i+1)*sizeof(char*));
            memcpy(p_node->p_data, &a[index], i - index + 1);
            printf("test %s\n", p_node->p_data);
            p_node->next = malloc(sizeof(node_t*));
            p_node = p_node->next;
            index = i + 1;
        }
    }
    return temp_p_node;
}

static node_t *sort_substring(node_t *head_node)
{
    node_t *p_i, *p_j;
    char *p_temp_data;
    for (p_i = head_node; p_i->next->next != NULL; p_i = p_i->next)
    {
        for (p_j = p_i->next; p_j->next != NULL; p_j = p_j->next)
        {
            if (compare_substrings(p_i->p_data, p_j->p_data))
            {
                p_temp_data = p_i->p_data;
                p_i->p_data = p_j->p_data;
                p_j->p_data = p_temp_data;
            }
        }
    }
    return head_node;
}

static void print_result(node_t *head_node)
{
    node_t *p_i;
    for (p_i = head_node; p_i->next != NULL; p_i = p_i->next)
    {
        for (int i = 0; i < strlen(p_i->p_data); i++)
        {
            printf("%c ", p_i->p_data[i]);
        }
    }
    printf("\n");
}

void main(void)
{
    char *p_result;
    p_result = input;
    print_result(sort_substring(find_substring(p_result)));
}
