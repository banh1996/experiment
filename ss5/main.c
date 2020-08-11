#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

// Size of the buffer
#define SIZE 1024
#define CHARACTER_MAX 10

// Special marker used to indicate end of the producer data
#define END_MARKER -1

#define log printf

char line1[SIZE];
char line2[CHARACTER_MAX];
char line3[SIZE];

static int g_count_line1 = 0;
static int g_count_line2 = 0;
static char g_is_end = 0;

// Initialize the mutex
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;

// Initialize the condition variables
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond3 = PTHREAD_COND_INITIALIZER;

void *input_thread(void *args)
{
    char c;
    while(memcmp(&line1[g_count_line1], "DONE", 4) && strlen(line1) != 4)
    {
        log("%s %d\n", __func__, __LINE__);
        pthread_mutex_lock(&mutex1);
        log("%s %d\n", __func__, __LINE__);
        if (g_count_line2 == CHARACTER_MAX)
            pthread_cond_wait(&cond1, &mutex1);
        log("%s %d\n", __func__, __LINE__);
        c = getchar();
        line1[g_count_line1] = c;
        g_count_line1++;

        pthread_cond_signal(&cond2);
        pthread_mutex_unlock(&mutex1);
    }
    g_is_end = 1;
    pthread_cond_signal(&cond2);
    return NULL;
}

void *line_separator_thread(void *args)
{
    while(!g_is_end)
    {
        log("%s %d\n", __func__, __LINE__);
        pthread_mutex_lock(&mutex1);
        log("%s %d\n", __func__, __LINE__);
        pthread_cond_wait(&cond2, &mutex1);
        log("%s %d\n", __func__, __LINE__);
        while (line2[g_count_line2] != '\0')
        {
            if (g_count_line2 == CHARACTER_MAX)
            {
                printf("%s\n", line2);
                memset(line1, 0, g_count_line2);
                g_count_line1 -= g_count_line2;
                memcpy(line1, &line1[g_count_line2], g_count_line1);
                g_count_line2 = 0;
                pthread_cond_signal(&cond1);
            }
            if (line2[g_count_line2] == '\n')
                line2[g_count_line2] = ' ';   
            g_count_line2++;
        }
        pthread_mutex_unlock(&mutex1);
    }
    return NULL;
}

int main(void)
{
    pthread_t p1, p2, p3, p4;
    g_is_end = 0;
    pthread_create(&p1, NULL, input_thread, NULL);
    pthread_create(&p2, NULL, line_separator_thread, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    return 0;
}
