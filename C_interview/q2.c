#include <stdio.h>
#include <stdint.h>

static int cal_step(int index, int step, int step_num, int bad_element)
{
    static int max = 0;
    if (max < index)
        max = index;
    if (step_num > 0)
    {
        if (index + step != bad_element)
            cal_step(index+step, step+1, step_num-1, bad_element);
        cal_step(index, step+1, step_num-1, bad_element);
    }
    else
    {
        return max;
    }
}

void main(void)
{
    int a = cal_step(0, 1, 2, 1);
    printf("a %d", a);
}