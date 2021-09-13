#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//The group of arguments passed to thread
struct thrd_data{
  long id;
  long start;
  long end; /* the sub-range is from start to end */
};
typedef struct {
  pthread_mutex_t     count_lock;     /* mutex semaphore for the barrier */
  pthread_cond_t      ok_to_proceed;  /* condition variable for leaving */
  long                count;      /* count of the number of threads who have  arrived */
} mylib_barrier_t;

//global variable
bool *GlobalList;//The list of nature number
long Num_Threads;
mylib_barrier_t barrier;/* barrier */

void mylib_barrier_init(mylib_barrier_t *b)
{
  b -> count = 0;
  pthread_mutex_init(&(b -> count_lock), NULL);
  pthread_cond_init(&(b -> ok_to_proceed), NULL);
}

void mylib_barrier(mylib_barrier_t *b, long id) 
{
   pthread_mutex_lock(&(b -> count_lock));
   b -> count ++;
   if (b -> count == Num_Threads)
   {
     b -> count = 0; /* must be reset for future re-use */
     pthread_cond_broadcast(&(b -> ok_to_proceed));
   }
   else
   {
    while (pthread_cond_wait(&(b -> ok_to_proceed), &(b -> count_lock)) !=    0);

    }
    pthread_mutex_unlock(&(b -> count_lock));
}

void mylib_barrier_destroy(mylib_barrier_t *b) 
{
  pthread_mutex_destroy(&(b -> count_lock));
  pthread_cond_destroy(&(b -> ok_to_proceed));
}

void *DoSieve(void *thrd_arg)
{

  struct thrd_data *t_data;
  long i,start, end;
  long k=2;//The current prime number in first loop
  long myid;

  /* Initialize my part of the global array */
  t_data = (struct thrd_data *) thrd_arg;
  myid = t_data->id;
  start = t_data->start;
  end = t_data->end;

  printf ("Thread %ld doing look-up from %ld to %ld\n", myid,start,end);
  //First loop: find all prime numbers that's less than sqrt(n)
  while (k*k<=end) 
  {
      int flag;
      if(k*k>=start)
        flag=0;
      else
        flag=1;
      //Second loop: mark all multiples of current prime number
      for (i = !flag? k*k-1:start+k-start%k-1; i <= end; i += k)
        GlobalList[i] = 1;
      i=k;
      //wait for other threads to finish the second loop for current prime   number
      mylib_barrier(&barrier,myid);
      //find next prime number that's greater than current one
      while (GlobalList[i] == 1)
            i++;
         k = i+1;

   }
  //decrement the counter of threads before exit
  pthread_mutex_lock (&barrier.count_lock);
  Num_Threads--;
  if (barrier.count == Num_Threads)
  {
    barrier.count = 0;  /* must be reset for future re-use */
    pthread_cond_broadcast(&(barrier.ok_to_proceed));
  }
  pthread_mutex_unlock (&barrier.count_lock);
  pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
  long i, n,n_threads;
  long k, nq, nr;
  FILE *results;
  struct thrd_data *t_arg;
  pthread_t *thread_id;
  pthread_attr_t attr;

  /* Pthreads setup: initialize barrier and explicitly create
   threads in a joinable state (for portability)  */
  mylib_barrier_init(&barrier);
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  /* ask to enter n and n_threads from the user */
  printf ("enter the range n = ");
  scanf ("%ld", &n);
  printf ("enter the number of threads n_threads = ");
  scanf ("%ld", &n_threads);
  time_t start = time(0);//set initial time
  //Initialize global list
  GlobalList=(bool *)malloc(sizeof(bool)*n);
  for(i=0;i<n;i++)
    GlobalList[i]=0;
  /* create arrays of thread ids and thread args */
  thread_id = (pthread_t *)malloc(sizeof(pthread_t)*n_threads);
  t_arg = (struct thrd_data *)malloc(sizeof(struct thrd_data)*n_threads);

  /* distribute load and create threads for computation */
  nq = n / n_threads;
  nr = n % n_threads;

  k = 1;
  Num_Threads=n_threads;
  for (i=0; i<n_threads; i++){
    t_arg[i].id = i;
    t_arg[i].start = k;
    if (i < nr)
        k = k + nq + 1;
    else
        k = k + nq;
    t_arg[i].end = k-1;
    pthread_create(&thread_id[i], &attr, DoSieve, (void *) &t_arg[i]);
  }

  /* Wait for all threads to complete then print all prime numbers */
  for (i=0; i<n_threads; i++) {
    pthread_join(thread_id[i], NULL);
  }
  int j=1;
  //Get the spent time for the computation works by all participanting threads
  time_t stop = time(0);
  printf("Time to do everything except print = %lu seconds\n", (unsigned   long)    (stop-start));
  //print the result of prime numbers
#if 0
  printf("The prime numbers are listed below:\n");
  for (i = 1; i < n; i++)
  {
    if (GlobalList[i] == 0)
    {
        printf("%ld ", i + 1);
        j++;
    }
    if (j% 15 == 0)
        printf("\n");
  }
  printf("\n");
#endif
j=0;
for (i = 1; i < n; i++)
  {
    if (GlobalList[i] == 0)
    {
        j++;
    }
  }
  printf("total: %d\n", j);
  // Clean up and exit 
  free(GlobalList);
  pthread_attr_destroy(&attr);
  mylib_barrier_destroy(&barrier); // destroy barrier object
  pthread_exit (NULL);
}