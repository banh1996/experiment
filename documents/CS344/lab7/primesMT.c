#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define debug_log(fmt, ...) \
                    if(isVerbose) \
                    fprintf(stderr, fmt, __VA_ARGS__);

typedef struct BitBlock_s
{
    uint32_t first_num;
    uint32_t last_num;
} BitBlock_t;

typedef struct mylib_barrier_s
{
  pthread_mutex_t     count_lock;
  pthread_cond_t      ok_to_proceed;
  uint32_t            count;
} mylib_barrier_t;

static mylib_barrier_t barrier;
static uint8_t isVerbose = 0;
static uint32_t g_count = 0;
static uint32_t g_num_thread = 1;
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

static void mylib_barrier_init(mylib_barrier_t *b)
{
    b -> count = 0;
    pthread_mutex_init(&(b -> count_lock), NULL);
    pthread_cond_init(&(b -> ok_to_proceed), NULL);
}

static void mylib_barrier(mylib_barrier_t *b) 
{
    pthread_mutex_lock(&(b -> count_lock));
    b -> count ++;
    if (b -> count == g_num_thread)
    {
        b -> count = 0;
        pthread_cond_broadcast(&(b -> ok_to_proceed));
    }
    else
    {
        while (pthread_cond_wait(&(b -> ok_to_proceed), &(b -> count_lock)) != 0);
    }
    pthread_mutex_unlock(&(b -> count_lock));
}

static void mylib_barrier_destroy(mylib_barrier_t *b) 
{
    pthread_mutex_destroy(&(b -> count_lock));
    pthread_cond_destroy(&(b -> ok_to_proceed));
}

static void *SieveOfEratosthenes(void *data)
{
    BitBlock_t *p_block = (BitBlock_t*)data;
    uint32_t a, p, i;
    debug_log("start thread %ld\nfirst: %d, last %d\n", pthread_self(), p_block->first_num, p_block->last_num);

    for (p = 2; p*p <= p_block->last_num; p++)
    {
		if (!helper_check_mask_index(p_bit_prime, p))
        {
            a = (p*p > p_block->first_num)?(p*p):(((p_block->first_num-1)/p)*p+p);
            //debug_log("log number here %d %d of thread %ld\n", p, a, pthread_self());
            for (i = a; i <= p_block->last_num; i += p)
            {
                //debug_log("test %d\n", i);
				helper_set_mask(p_bit_prime, i);
            }
            mylib_barrier(&barrier);
        }
    }

    free(p_block);
    //decrement the counter of threads before exit
    pthread_mutex_lock (&barrier.count_lock);
    g_num_thread--;
    if (barrier.count == g_num_thread)
    {
        barrier.count = 0;  /* must be reset for future re-use */
        pthread_cond_broadcast(&(barrier.ok_to_proceed));
    }
    pthread_mutex_unlock (&barrier.count_lock);

    debug_log("end thread %ld\n", pthread_self());
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    int opt;
    uint32_t n = 10240, num_thread = 1, i;
    pthread_t *p_thread_id;
    pthread_attr_t attr;
    BitBlock_t *p_block;
    time_t start, end;

    while ((opt = getopt(argc, argv, "t:u:hv")) != -1) {
        switch (opt) {
        case 't':
            g_num_thread = (uint32_t)atoi(optarg);
            num_thread = g_num_thread;
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

    p_bit_prime = (uint32_t*)calloc((n + 2)/32, sizeof(uint32_t));
    mylib_barrier_init(&barrier);
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    if (g_num_thread > 0)
    {
        p_thread_id = (pthread_t *)calloc(g_num_thread, sizeof(pthread_t));
        for (i = 0; i < g_num_thread; i++)
        {
            p_block = (BitBlock_t*)calloc(1, sizeof(BitBlock_t));
            p_block->first_num = i*n/g_num_thread + 2;
            if (i != g_num_thread - 1)
                p_block->last_num = (i + 1)*n/g_num_thread + 1;
            else
                p_block->last_num = n;
            pthread_create(&p_thread_id[i], &attr, SieveOfEratosthenes, (void*)p_block);
        }

        for (i = 0; i < num_thread; i++)
        {
            pthread_join(p_thread_id[i], NULL);
        }
        debug_log("%d threads remain\n", g_num_thread);
    }

    if (isVerbose)
    {
        time(&end);
        fprintf(stderr, "second: %ld\n", end - start);
    }

    for (uint32_t p = 2; p <= n; p++)
    {
		if (!helper_check_mask_index(p_bit_prime, p))
        {
            printf("%d \n", p);
            //g_count++;
        }
    }

    debug_log("total: %d\n", g_count);
    free(p_bit_prime);
    pthread_attr_destroy(&attr);
    mylib_barrier_destroy(&barrier);

    if (num_thread > 0)
        free(p_thread_id);

    return 0;
}
