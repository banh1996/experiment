#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

// Size of the buffer
#define SIZE 100
#define CHARACTER_MAX 10

// Special marker used to indicate end of the producer data
char end_string[6] = "\nDONE\n";

#define log printf
//#define log

char line1[CHARACTER_MAX*2];
char line2[CHARACTER_MAX*2];
char line3[CHARACTER_MAX];

static int g_count_line1 = 0;
static int g_count_line2 = 0;
static int g_count_line3 = 0;
static int real_line_count = 0;
static char g_is_end = 0;

// Initialize the mutex
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;

// Initialize the condition variables
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond3 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond4 = PTHREAD_COND_INITIALIZER;

void *input_thread(void *args)
{
    char c, end_count = 0;
    while(1)
    {
        pthread_mutex_lock(&mutex1);
        if (g_count_line1 != g_count_line2)
        {
            pthread_cond_wait(&cond1, &mutex1);
        }
        c = getchar();
        line1[g_count_line1] = c;
        g_count_line1++;

        if(end_string[end_count] == c)
        {
            end_count++;
            if (end_count >= 6)
                break;
        }
        else
        {
            end_count = 0;
        }

        pthread_cond_signal(&cond2);
        pthread_mutex_unlock(&mutex1);
    }
    printf("end\n");
    g_is_end = 1;
    pthread_cond_signal(&cond2);
    pthread_mutex_unlock(&mutex1);
    return NULL;
}

void *line_separator_thread(void *args)
{
    while(!g_is_end)
    {
        log("%s %d\n", __func__, __LINE__);
        pthread_mutex_lock(&mutex1);
    /////
        pthread_mutex_lock(&mutex2);
    /////
        if (g_count_line1 == g_count_line2)
        {
            log("%s %d\n", __func__, __LINE__);
            pthread_cond_wait(&cond2, &mutex1);
        }
        log("%s %d\n", __func__, __LINE__);
        if (line1[g_count_line2] != '\0')
        {
            line2[g_count_line2] = line1[g_count_line2];
            if (line2[g_count_line2] == '\n')
                line2[g_count_line2] = ' ';
    /////
            if (g_count_line2 != g_count_line3)
            {
                log("%s %d %d %d\n", __func__, __LINE__, g_count_line2, g_count_line3);
                pthread_cond_wait(&cond3, &mutex2);
            }
            pthread_cond_signal(&cond4);
            pthread_mutex_unlock(&mutex2);
    /////
            g_count_line2++;
            pthread_cond_signal(&cond1);
            #if 0
            if (g_count_line2 == CHARACTER_MAX && !g_is_end)
            {
                printf("%s\n", line2);
                memset(line1, 0, sizeof(line1));
                memset(line2, 0, sizeof(line2));
                g_count_line1 = 0;
                g_count_line2 = 0;
            }
            
            log("%s %d\n", __func__, __LINE__);
            pthread_mutex_lock(&mutex2);
            g_count_line2--;
            if (g_count_line2 != g_count_line3)
            {
                log("%s %d %d %d\n", __func__, __LINE__, g_count_line2, g_count_line3);
                pthread_cond_wait(&cond3, &mutex2);
            }
            log("%s %d\n", __func__, __LINE__);
            g_count_line2++;
            pthread_cond_signal(&cond4);
            pthread_mutex_unlock(&mutex2);
            #endif
        }
        pthread_mutex_unlock(&mutex1);
        //g_count_line2++;
    }
    return NULL;
}

void *plus_sign_thread(void *args)
{
    while(!g_is_end)
    {
        log("%s %d\n", __func__, __LINE__);
        pthread_mutex_lock(&mutex2);
        if (g_count_line2 == g_count_line3)
        {
            log("%s %d\n", __func__, __LINE__);
            pthread_cond_wait(&cond4, &mutex2);
        }
        log("%s %d\n", __func__, __LINE__);
        if (line2[g_count_line3] != '\0')
        {
            line3[real_line_count] = line2[g_count_line3];
            if (g_count_line3 > 1 && line3[g_count_line3] == '+' && line3[g_count_line3-1] == '+')
            {
                line3[real_line_count] = '^';
                real_line_count--;
            }
            g_count_line3++;
            real_line_count++;
            
            if (real_line_count == CHARACTER_MAX && !g_is_end)
            {
                printf("%s\n", line3);
                memset(line1, 0, sizeof(line1));
                memset(line2, 0, sizeof(line2));
                memset(line3, 0, sizeof(line3));
                g_count_line1 = 0;
                g_count_line2 = 0;
                g_count_line3 = 0;
                real_line_count = 0;
            }
            pthread_cond_signal(&cond3);
        }
        pthread_mutex_unlock(&mutex2);
    }
    return NULL;
}

int main(void)
{
    pthread_t p1, p2, p3, p4;
    g_is_end = 0;
    memset(line1, 0, sizeof(line1));
    memset(line2, 0, sizeof(line2));
    memset(line3, 0, sizeof(line3));
    pthread_create(&p3, NULL, plus_sign_thread, NULL);
    pthread_create(&p2, NULL, line_separator_thread, NULL);
    pthread_create(&p1, NULL, input_thread, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    return 0;
}
