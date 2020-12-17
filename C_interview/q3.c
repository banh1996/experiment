#include <stdio.h>
#include <stdint.h>

static int a[5] = {-2, 3, 1, -5, -1};

void main(void)
{
    int i, index = 0, save_index = 0, sum = 0, min_sum = 999, num;
    for (i = 0; i < 5; i++)
    {
        if (a[i] < 0)
        {
            if (sum == 0)
                index = i;
            sum += a[i];
        }
        else
        {
            sum = 0;
        }

        if (sum < min_sum)
        {
            save_index = index;
            min_sum = sum;
        }
    }

    sum = 0;
    for (i = save_index; i < 5; i++)
    {
        if (a[i] < 0)
            sum += a[i];
        else
            break;        
    }

    if (sum < 0)
    {
        num = ~(sum - 1) + 1;
        for (i = save_index - 1; i >= 0; i--)
        {
            num -= a[i];
        }
        printf("%d", num);
    }
    else
        printf("0");
}