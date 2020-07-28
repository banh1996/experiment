#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct BitBlock_s
{
    uint32_t first_num;
    uint32_t last_num;
	pthread_mutex_t mutex;
} BitBlock_t;

static uint8_t isVerbose = 0;
static uint32_t g_count = 0;
static uint32_t *p_bit_prime;

static uint8_t helper_check_mask_index(uint32_t *mask, uint32_t index)
{
    uint32_t num = *(mask + index/32);
    if(num & (1 << (index%32)))
        return 0x01;
    return 0x00;
}

static void helper_set_mask(uint32_t *mask, uint32_t index)
{
    uint32_t *num = (mask + index/32);
    *num |= (1 << (index%32));
}

static void *SieveOfEratosthenes(void *data)
{
    BitBlock_t *p_block = (BitBlock_t*)data;
    pthread_mutex_lock(p_block->mutex);
    uint32_t n = p_block->last_num - p_block-first_num;

    for (uint32_t p = 2; p*p <= p_block->last_num; p++)
    {
		if (!helper_check_mask_index(p_bit_prime, p))
        {
            for (uint32_t i = p*p; i <= n; i += p)
				helper_set_mask(p_bit_prime, i);
        }
    }

    for (uint32_t p = p_block->first_num; p <= p_block->last_num; p++)
		if (!helper_check_mask_index(p_bit_prime, p))
            //printf("%d ", p);
            g_count++;

    if (isVerbose)
        fprintf(stderr, "count: %d\n", g_count);
    free(data);
    pthread_mutex_unlock(p_block->mutex);
}

int main(int argc, char *argv[])
{
    int opt;
    uint32_t thread_num = 1, n = 10240, *first_num, *last_num;
    pthread_t *p_thread_id;
    time_t start, end;
    BitBlock_t *p_block;
    while ((opt = getopt(argc, argv, "t:u:hv")) != -1) {
        switch (opt) {
        case 't':
            thread_num = (uint32_t)atoi(optarg);
            break;
        case 'u':
            n = (uint32_t)atoi(optarg);
            break;
        case 'h':
            // Show something helpful
            fprintf(stdout, "You must be out of your Vulcan mind if you think\n"
                    "I'm going to put helpful things in here.\n\n");
            exit(EXIT_SUCCESS);
            break;
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

    p_bit_prime = (uint32_t*)calloc((n + 1)/32, sizeof(uint32_t));
    if (thread_num > 0)
    {
        p_thread_id = calloc(thread_num, sizeof(pthread_t));
        for (uint32_t i = 0; i < thread_num; i++)
        {
            p_block = (BitBlock_t*)calloc(1, sizeof(BitBlock_t));;
            p_block->first_num = i*n/thread_num + 2;
            *first_num = i*n/thread_num + 2;
            if (i != thread_num - 1)
                p_block->last_num = (i + 1)*n/thread_num + 1;
            else
                p_block->last_num = n;
            pthread_create(&p_thread_id[i], NULL, SieveOfEratosthenes, (void*)p_block);
        }

        if (isVerbose)
        {   
            fprintf(stderr, "created all thread\n");
        }

        for (uint32_t i = 0; i < thread_num; i++)
        {
            pthread_join(p_thread_id[i], NULL);
        }
        free(p_thread_id);
    }
    free(p_bit_prime);

    if (isVerbose)
    {
        time(&end);
        fprintf(stderr, "second: %ld\n", end - start);
    }

    return 0;
}
