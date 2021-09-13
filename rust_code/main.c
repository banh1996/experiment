#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h> 
#include <errno.h> 
#include <unistd.h>

#define MAX_CHARACTER_NUMBER 80
#define UNUSED(x) (void)(x)

// stop character
static char stop_str[6] = "\nSTOP\n";

// need init buffer 1&2 in case the input characters are all "+"
static char buffer1[2 * MAX_CHARACTER_NUMBER];
static char buffer2[2 * MAX_CHARACTER_NUMBER];
// buffer3 is the output array
static char buffer3[MAX_CHARACTER_NUMBER];

static int fd_in = STDIN_FILENO;
static int fd_out = STDOUT_FILENO;

static int buffer1_index = 0;
static int buffer2_index = 0;
static int buffer3_index = 0;
static int output_line_index = 0;
// static char first_cha;

//the variable to check input is stop
static char is_stop_input = 0;

// mutexs
static pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;

// condition variables
static pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
static pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
static pthread_cond_t cond3 = PTHREAD_COND_INITIALIZER;
static pthread_cond_t cond4 = PTHREAD_COND_INITIALIZER;
static pthread_cond_t cond5 = PTHREAD_COND_INITIALIZER;
static pthread_cond_t cond6 = PTHREAD_COND_INITIALIZER;

static void *read_input_t(void *args)
{
    char c;
    int stop_index = 0;
    UNUSED(args);
    while(1)
    {
        pthread_mutex_lock(&mutex1);
        if (buffer1_index != buffer2_index)
        {
            pthread_cond_wait(&cond1, &mutex1);
        }

        if (output_line_index == MAX_CHARACTER_NUMBER)
        {
            pthread_mutex_unlock(&mutex1);
            continue;
        }
        usleep(200);

        read(fd_in, &c, 1);
        
        buffer1[buffer1_index] = c;
        buffer1_index++;

        if(stop_str[stop_index] == c)
        {
            stop_index++;
            if (stop_index >= 6)
                break;
        }
        else
        {
            stop_index = 0;
        }
        usleep(100);
        pthread_cond_signal(&cond2);
        pthread_mutex_unlock(&mutex1);
    }

    is_stop_input = 1;
    // send signal release to cond2,3,4,5,6
    pthread_cond_signal(&cond2);
    pthread_cond_signal(&cond3);
    pthread_cond_signal(&cond4);
    pthread_cond_signal(&cond5);
    pthread_cond_signal(&cond6);
    pthread_mutex_unlock(&mutex1);
    return NULL;
}

static void *line_separator_t(void *args)
{
    UNUSED(args);
    while(!is_stop_input)
    {
        pthread_mutex_lock(&mutex1);

        if (buffer1_index == buffer2_index)
        {
            pthread_cond_wait(&cond2, &mutex1);
        }
        if (buffer1[buffer2_index] != '\0')
        {
            buffer2[buffer2_index] = buffer1[buffer2_index];
            if (buffer2[buffer2_index] == '\n')
                buffer2[buffer2_index] = ' ';
            buffer2_index++;
            usleep(50);
            pthread_cond_signal(&cond1);
            pthread_mutex_unlock(&mutex1);

            pthread_mutex_lock(&mutex2);
            if (buffer2_index != buffer3_index && buffer1_index != buffer2_index)
            {
                pthread_cond_wait(&cond3, &mutex2);
            }
            pthread_cond_signal(&cond4);
            pthread_mutex_unlock(&mutex2);
        }
    }
    return NULL;
}

static void *convert_plus_t(void *args)
{
    UNUSED(args);
    while(!is_stop_input)
    {
        pthread_mutex_lock(&mutex2);
        if (buffer2_index == buffer3_index)
        {
            pthread_cond_wait(&cond4, &mutex2);
        }

        if (buffer2[buffer3_index] != '\0')
        {
            buffer3[output_line_index] = buffer2[buffer3_index];
            if (output_line_index > 1 && buffer3[output_line_index] == '+' &&
                buffer3[output_line_index-1] == '+')
            {
                buffer3[output_line_index] = '\0';
                buffer3[--output_line_index] = '^';
            }
            buffer3_index++;
            output_line_index++;

            pthread_cond_signal(&cond3);
        }
        pthread_mutex_unlock(&mutex2);

        pthread_mutex_lock(&mutex3);
        if (output_line_index == MAX_CHARACTER_NUMBER && !is_stop_input)
        {
            pthread_cond_signal(&cond6);
            pthread_cond_wait(&cond5, &mutex3);
        }
        pthread_mutex_unlock(&mutex3);
    }
    return NULL;
}
static void *write_output_t(void *args)
{
    UNUSED(args);
    while(!is_stop_input)
    {
        pthread_mutex_lock(&mutex3);
        if (output_line_index != MAX_CHARACTER_NUMBER && !is_stop_input)
        {
            pthread_cond_wait(&cond6, &mutex3);
        }
        if (is_stop_input)
            break;
        write(fd_out, buffer3, strlen(buffer3));
        write(fd_out, "\n", 1);
        buffer1_index = 0;
        buffer2_index = 0;
        buffer3_index = 0;
        buffer1[0] = buffer2[0] = buffer3[0] = buffer1[strlen(buffer1) - 1];
        memset(buffer1, 0, sizeof(buffer1));
        memset(buffer2, 0, sizeof(buffer2));
        memset(buffer3, 0, sizeof(buffer3));
        output_line_index = 0;
        pthread_cond_signal(&cond5);
        pthread_mutex_unlock(&mutex3);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    int opt;
    pthread_t p1, p2, p3, p4;

    while ((opt = getopt(argc, argv, ">:<:")) != -1)
    {
        switch (opt)
        {
        case '<': //input file
            fd_in = open(optarg, O_RDONLY);
            if(fd_in == -1)
            {
                perror("file not found.\n");
                return -1;
            }
            break;
        case '>': //output file
            fd_out = open(optarg, O_WRONLY|O_CREAT|O_TRUNC,  S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
            if(fd_out == -1)
            {
                perror("file cannot create.\n");
                return -1;
            }
            break;
        default:
            break;
        }
    }

    is_stop_input = 0;
    memset(buffer1, 0, sizeof(buffer1));
    memset(buffer2, 0, sizeof(buffer2));
    memset(buffer3, 0, sizeof(buffer3));
    pthread_create(&p4, NULL, write_output_t, NULL);
    pthread_create(&p3, NULL, convert_plus_t, NULL);
    pthread_create(&p2, NULL, line_separator_t, NULL);
    pthread_create(&p1, NULL, read_input_t, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    pthread_join(p4, NULL);

    while(1);
    return 0;
}
