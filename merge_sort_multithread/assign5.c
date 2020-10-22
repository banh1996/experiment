#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

static uint8_t isVerbose = 0;
static int *p_array;
static sem_t sem;

void debug_log(char *fmt, ...)
{
    va_list args;
    if (isVerbose) {
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    }
}

// merge function for merging two parts
void merge(uint32_t low, uint32_t mid, uint32_t high)
{
    int *left = malloc((mid - low + 1)*sizeof(int));
    int *right = malloc((high - mid)*sizeof(int));

    // n1 is size of left part and n2 is size
    // of right part
    uint32_t length_left = mid - low + 1;
    uint32_t length_right = high - mid;
    uint32_t i = 0, j = 0, k = low;

    // storing values in left part
    for (i = 0; i < length_left; i++)
        left[i] = p_array[i + low];

    // storing values in right part
    for (i = 0; i < length_right; i++)
        right[i] = p_array[i + mid + 1];

    i = 0;
    // merge left and right in ascending order
    while (i < length_left && j < length_right)
    {
        if (left[i] <= right[j])
            p_array[k++] = left[i++];
        else
            p_array[k++] = right[j++];
    }

    // insert remaining values from left
    while (i < length_left) {
        p_array[k++] = left[i++];
    }

    // insert remaining values from right
    while (j < length_right) {
        p_array[k++] = right[j++];
    }

    free(left);
    free(right);
}

// merge sort function
static void mergeSort(uint32_t low, uint32_t high)
{
    // calculating mid point of array
    uint32_t mid = low + (high - low) / 2;
    if (low < high)
    {
        // calling first half 
        mergeSort(low, mid);

        // calling second half
        mergeSort(mid + 1, high);

        // merging the two halves
        merge(low, mid, high);
    }
}

static void *createArray(void *data)
{
    debug_log("t1\n");
    uint32_t n = *(int*)data, i;
    srand(time(NULL));
    p_array = malloc(n*sizeof(int));

    for (i = 0; i < n; i++)
    {
        p_array[i] = rand() % 2001 - 1000;
        //printf("%d\t", p_array[i]);
    }
    debug_log("\nend created\n");
    sem_post(&sem);
    sem_post(&sem);
}

static void *sortFirstHalf(void *data)
{
    debug_log("t2\n");
    uint32_t high = *(uint32_t*)data - 1, i;
    debug_log("array 1, length 0 - %d\n", high);
    mergeSort(0, high);
    for (i = 0; i <= high; i++)
        debug_log("*%d ", p_array[i]);
    debug_log("\n");
    sem_post(&sem);
}

static void *sortSecondHalf(void *data)
{
    debug_log("t3\n");
    uint32_t low = *(uint32_t*)data;
    uint32_t high = *((uint32_t*)data + 1), i;
    debug_log("array 2, length %d - %d\n", low, high);
    mergeSort(low, high);
    for (i = low; i <= high; i++)
        debug_log("**%d ", p_array[i]);
    debug_log("\n");
    sem_post(&sem);
}

static void *mergeTwoHalves(void *data)
{
    debug_log("t4\n");
    uint32_t mid = *(uint32_t*)data - 1;
    uint32_t high = *((uint32_t*)data + 1);
    merge(0, mid, high);
    sem_post(&sem);
    sem_post(&sem);
}

static void *printSortedArray(void *data)
{
    debug_log("t5\n");
    uint32_t high = *((uint32_t*)data + 1), i;
    debug_log("result:\n");
    for (i = 0; i <= high; i++)
        printf("%d\t", p_array[i]);
    printf("\n");
    sem_post(&sem);
    sem_post(&sem);
}

int main(int argc, char *argv[])
{
    int opt;
    uint32_t i, n, length[2];
    pthread_t th1, th2, th3, th4, th5;
    pthread_attr_t attr;
    time_t start, end;

    if (argc < 2)
    {
        printf("lack of argument\n");
        return -1;
    }

    n = atoi(argv[1]);

    // run ./assign5 -v to see debug log info
    while ((opt = getopt(argc, argv, ":v")) != -1) {
        switch (opt) {
        case 'v':
            isVerbose = 1;
            fprintf(stderr, "verbose: verbose option on\n");
            break;
        default:
            break;
        }
    }

    if (isVerbose)
    {
        fprintf(stderr, "n: %d\n", n);
        time(&start);
    }

    sem_init(&sem, 0, 2);
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    // split and sort 2 arrays
    length[0] = n/2;
    length[1] = n-1;

    // create random array
    sem_wait(&sem);
    sem_wait(&sem);
    pthread_create(&th1, &attr, createArray, (void*)&n);
    sem_wait(&sem);
    sem_wait(&sem);
    pthread_create(&th2, &attr, sortFirstHalf, (void*)&length);
    pthread_create(&th3, &attr, sortSecondHalf, (void*)&length);
    // merge 2 arrays
    sem_wait(&sem);
    sem_wait(&sem);
    pthread_create(&th4, &attr, mergeTwoHalves, (void*)&length);
    // print result
    sem_wait(&sem);
    sem_wait(&sem);
    pthread_create(&th5, &attr, printSortedArray, (void*)&length);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);
    pthread_join(th4, NULL);
    pthread_join(th5, NULL);

    sem_destroy(&sem); 

    free(p_array);

    if (isVerbose)
    {
        time(&end);
        fprintf(stderr, "timerun: %ld\n", end - start);
    }

    debug_log("end\n");
    pthread_attr_destroy(&attr);

    return 0;
}
