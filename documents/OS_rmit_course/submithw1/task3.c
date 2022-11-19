#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "common_def.h"

typedef struct word_index_t
{
    int *data;
    int length;
} word_index_t;

static char *g_wordlist[2222222];
static int g_word_number = 0;
static int g_fifo_fd[13];

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


static void filter(char *f_in)
{
    int fd_in = open(f_in, O_RDONLY);
    int read_bytes;
    int file_read_stop = 0;
    int is_keep_this_line = 0x01;
    int indexCurrentSymbol = 0;
    char buf[BUFFSIZE];


    while (file_read_stop == 0)
    {
        read_bytes = read(fd_in, &buf[indexCurrentSymbol], 1); 
        if (read_bytes == -1) 
        {
            fprintf(stderr, "read %s while: -1", f_in);
            break;
        }

        if (read_bytes == 0)
        {
            file_read_stop = 1;
        }

        if (buf[indexCurrentSymbol] == DELIM_STR || buf[indexCurrentSymbol] == EOF)
        {
            //TODO
            if (indexCurrentSymbol < 3 || indexCurrentSymbol > 15)
                is_keep_this_line = 0;
            if (is_keep_this_line == 0x01)
            {
                //place to output buffer
                g_wordlist[g_word_number] = malloc(indexCurrentSymbol+1);
                memcpy(g_wordlist[g_word_number], buf, indexCurrentSymbol+1);
                g_word_number++;
            }
            indexCurrentSymbol = 0;
            is_keep_this_line = 0x01;
            memset(buf, 0, sizeof(buf));
        }
        else
        {
            indexCurrentSymbol++;
        }
    }
    close(fd_in);
    //return g_wordlist;
}

static int cmpfunc (const void * a, const void * b) {
   return ( g_wordlist[*(int*)a][2] - g_wordlist[*(int*)b][2] );
}

static void* map3_thread(void* p)
{
    word_index_t *word_index = (word_index_t*)p;
    int fd;

    qsort(word_index->data, word_index->length, sizeof(int), cmpfunc);


    //write fifo
    fd = g_fifo_fd[strlen(g_wordlist[word_index->data[0]])-4];

    for (int i = 0; i < word_index->length; i++) {
        write(fd, g_wordlist[word_index->data[i]], strlen(g_wordlist[word_index->data[i]]));
    }
    write(fd, "END\n", 4);

    //close(fd);

    pthread_exit(NULL);
}

static void* map3(void* p)
{
    word_index_t *word_indexes[13];
    pthread_t tid[13];
    (void)p;

    for (int i = 0; i < 13; i++)
    {
        word_indexes[i] = calloc(1, sizeof(word_index_t));
        word_indexes[i]->data = malloc(999999*sizeof(int));
    }

    for (int i = 0; i < g_word_number; i++)
    {
        int index = strlen(g_wordlist[i])-4;
        // printf("b-%d-%d\n", index, cur_word_indexes[index]);
        //*(word_indexes[index] + cur_word_indexes[index]++) = i;
        word_indexes[index]->data[word_indexes[index]->length++] = i;
    }

    //create fifo files
    for (int i = 0; i < 13; i++)
    {
        char myfifo[20] = "myfifo\0\0\0";
        sprintf(&myfifo[strlen(myfifo)], "%d", i+3);
        if (mkfifo(myfifo, 0666) == -1)
        {
            //fprintf(stderr, "Server: Couldn’t create %s FIFO.\n", myfifo);
            //exit(1);
        }
        g_fifo_fd[i] = open(myfifo, O_WRONLY);
    }

    for (int i = 0; i < 13; i++)
        pthread_create(&tid[i], NULL, map3_thread, (void*)word_indexes[i]);

    //pthread_mutex_lock(&lock);
    //printf("wait\n");
    pthread_cond_wait(&cond, &lock);
    //printf("wait done\n");

    for (int i = 0; i < 13; i++)
        pthread_join(tid[i], NULL);

    // pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);

    for (int i = 0; i < 13; i++)
        close(g_fifo_fd[i]);


    for (int i = 0; i < 13; i++)
    {
        free(word_indexes[i]->data);
        free(word_indexes[i]);
    }

    pthread_exit(NULL);
    //return 0;
}


static void* reduce3(void* p)
{
    int fd_in[13];
    char buf[13][BUFFSIZE];
    char continue_reads[13];
    int readbyte = 0;
    int temp_index = 14;
    char min_str[BUFFSIZE];

    (void)p;
    pthread_mutex_lock(&lock);
    //pthread_cond_wait(&cond, &lock);
    memset(continue_reads, 1, sizeof(continue_reads));
    for (int i = 0; i < 13; i++)
    {
        char myfifo[20] = "myfifo\0\0\0\0\0\0\0";
        sprintf(&myfifo[strlen(myfifo)], "%d", i+3);
        if (mkfifo(myfifo, 0666) == -1)
        {
            //fprintf(stderr, "Server: Couldn’t create %s FIFO.\n", myfifo);
            //exit(1);
        }
        fd_in[i] = open(myfifo, O_RDONLY);
    }

    while (1)
    {
        //read line each file
        for (int i = 0; i < 13; i++)
        {
            if (continue_reads[i])
            {
                memset(&buf[i], 0, BUFFSIZE);
                if ((readbyte = read(fd_in[i], buf[i], i+4)) > 0)
                {
                    continue_reads[i] = 0;
                    //fprintf(stdout, "%d:%s", readbyte-1, buf[i]);
                }
                else
                    printf("err %s %d\n", __func__, readbyte);

                if (memcmp("END", buf[i], 3) == 0)
                    memset(buf[i], 'z', BUFFSIZE);
            }
        }

        //find the lowest order
        temp_index = 14;
        memset(min_str, 'z', BUFFSIZE);
        for (int i = 0; i < 13; i++)
        {
            if (continue_reads[i] == 0 && strcmp(&min_str[2], &buf[i][2]) > 0)
            {
                // printf("asd: %d %s", i+3, buf[i]);
                memset(min_str, 0, BUFFSIZE);
                sprintf(min_str, "%s", buf[i]);
                temp_index = i;
            }
        }

        //handle the minimum character
        if (temp_index > 12)
        {
            //fprintf(stderr, "error while running reduces\n");
            break;
        }
        continue_reads[temp_index] = 1;
        //fprintf(stdout, "%s", buf[temp_index]);
        write(STDOUT_FILENO, buf[temp_index], temp_index+4);
    }


    for (int i = 0; i < 13; i++)
        close(fd_in[i]);

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);
    //return 0;
}

int main(int argc, char *argv[])
{
    pthread_t id1, id2;
    if (argc < 2)
        fprintf(stderr, "lack of argument\n");

    filter(argv[1]);

    pthread_create(&id1, NULL, map3, NULL);
    pthread_create(&id2, NULL, reduce3, NULL);
    pthread_join(id1, NULL);
    pthread_join(id2, NULL);

    for (int i = 0; i < g_word_number; i++)
    {
        free(g_wordlist[i]);
    }

    return 0;
}