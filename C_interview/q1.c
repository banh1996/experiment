#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define BUF_LEN  50

static char input[BUF_LEN] = {1, 1, 0, 1, 0, 0, 1, 1, 0, 0};

static int compare_substrings(char *a1, char *a2, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (a1[i] > a2[i])
            return 0;
        if (a1[i] < a2[i])
            return 1;
    }
    return 0;
}

static char *swap_substrings(char *a, int first, int index, int last, int len)
{
    char *buf;
    buf = (char*)malloc(len*sizeof(char*));
    memcpy(buf, a, len);
    for (int i = index; i >= first; i--)
    {
        buf[last-index+i] = a[i];
    }

    for (int i = index+1; i <= last; i++)
    {
        buf[first+i-index-1] = a[i];
    }

    return buf;
}

static char *get_max_number_substring(char *a, int index, int len)
{
    int i, j, count1 = 0, count0 = 0, first = index, last = index+1;
    char *p_result, *ptr;
    p_result = (char*)malloc(len*sizeof(char*));
    memset(p_result, 0, len);
    memcpy(p_result, a, len);
    while (first != 0 || last != len-1)
    {
        count1 = 0;
        count0 = 0;
        for (i = first; i >= 0; i--)
        {
            if (a[i])
                count1++;
            else
                count0++;
            if (count1 > count0)
                break;
            if (count1 == count0)
            {
                first = i;
                break;
            }
        }
        if (count1 != count0)
            break;

        count1 = 0;
        count0 = 0;
        for (i = last; i < len; i++)
        {
            if (a[i])
                count1++;
            else
                count0++;
            if (count1 == count0)
            {
                last = i;
                break;
            }
        }
        if (count1 != count0)
            break;

        ptr = swap_substrings(a, first, index, last, len);

        if (compare_substrings(a, ptr, len))
        {
            memcpy(p_result, ptr, len);
            free(ptr);
        }
    }
    return p_result;
}

static void print_result(char *a, int len)
{
    for (int i = 0; i < len; i++)
        printf("%d ", a[i]);
    printf("\n");
}

void main(void)
{
    int len = 10;
    char *p_result, *ptr;
    p_result = input;
    for (int i = 1; i < len; i++)
    {
        ptr = get_max_number_substring(input, i, len);
        if (compare_substrings(p_result, ptr, len))
        {
            if (p_result != input)
                free(p_result);
            p_result = ptr;
        }
        else
        {
            free(ptr);
        }
    }
    print_result(p_result, len);
    if (p_result != input)
        free(p_result);
}
