#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Size of the buffer
#define SIZE 5

// Special marker used to indicate end of the producer data
#define END_MARKER -1

// Buffer, shared resource
int buffer[SIZE];
// Number of items in the buffer, shared resource
int count = 0;
// Index where the producer will put the next item
int prod_idx = 0;
// Index where the consumer will pick up the next item
int con_idx = 0;
// How many items will be produced
int num_iterations = 0;

// Initialize the mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Initialize the condition variables
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;

/*
 Produce an item. Produces a random integer between [0, 1000] unless it is the last item to be produced in which case the value -1 is returned.
*/
#if 0
int produce(int i)
{
    int value;
    if (i == num_iterations - 1)
        value = END_MARKER;
    else
        value = rand() % 1000;
    buffer[prod_idx] = value;
    // Increment the index where the next item will be put. Roll over to the start of the buffer if the item was placed in the last slot in the buffer
    prod_idx = (prod_idx + 1) % SIZE;
    count++;
    return value;
}
#endif

/*
 Function that the producer thread will run. Produce an item and put in the buffer only if there is space in the buffer. If the buffer is full, then wait until there is space in the buffer.
*/
void *producer(void *args)
{
    //for (int i = 0; i < num_iterations; i++)
    int i = 0;
    while(memcmp(line, "DONE", 4))
    {
      memset(line, 0, sizeof(line));
      i = 0;
      while (count == SIZE)
        // Buffer is full. Wait for the consumer to signal that the buffer has space
        pthread_cond_wait(&empty, &mutex);
      //do
      {
        // Lock the mutex before checking where there is space in the buffer
        pthread_mutex_lock(&mutex);
        //printf("PROD %d\n", produce(i));
        c = getchar();
        line[i] = c;
        i++;
      }
      //while(c != '\n');
      i--;
      // Signal to the consumer that the buffer is no longer empty
      pthread_cond_signal(&full);
      // Unlock the mutex
      pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

/*
 Get the next item from the buffer
*/
#if 0
int consume()
{
    int value = buffer[con_idx];
    // Increment the index from which the item will be picked up, rolling over to the start of the buffer if currently at the end of the buffer
    con_idx = (con_idx + 1) % SIZE;
    count--;
    return value;
}
#endif

/*
 Function that the consumer thread will run. Get  an item from the buffer if the buffer is not empty. If the buffer is empty then wait until there is data in the buffer.
*/
void *consumer(void *args)
{
    int value = 0;
    // Continue consuming until the END_MARKER is seen    
    //while (value != END_MARKER)
    {
      // Lock the mutex before checking if the buffer has data      
      pthread_mutex_lock(&mutex);
      while (count == 0)
        // Buffer is empty. Wait for the producer to signal that the buffer has data
        pthread_cond_wait(&full, &mutex);
      //value = consume();
      //printf("CONS %d\n", value);
      if (line[i] == '\n')
        line[i] = ' ';
      else if (i > 1 && line[i] == '+' && line[i-1] == '+')
      {
        line[i] = '\0';
        line[i-1] = '^';
        i--;
      }
      // Signal to the producer that the buffer has space
      pthread_cond_signal(&empty);
      // Unlock the mutex
      pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    int pipe1[2], pipe2[2], pipe3[2];
    if (argc != 2)
    {
      printf("Usage: ./main num_iterations\n");
      printf("\tProvide number of iterations for the program as an integer greater than 0\n");
      exit(1);
    }
    //srand(time(0));
    num_iterations = atoi(argv[1]);
    // Create the producer and consumer threads
    pthread_t p, c;
    pthread_create(&p, NULL, producer, NULL);
    // Sleep for a few seconds to allow the producer to fill up the buffer. This has been put in to demonstrate the the producer blocks when the buffer is full. Real-world systems won't have this sleep    
    // sleep(5);
    pthread_create(&c, NULL, consumer, NULL);
    pthread_join(p, NULL);
    pthread_join(c, NULL);
    return 0;
}
