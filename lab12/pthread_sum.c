/* 
  Simple Pthread Program to find the sum of a vector.
  Uses mutex locks to update the global sum. 
  Author: Aniket Bagaitkar 
  Date: 04/12/2022

  To Compile: gcc -O pthr pthread_sum.c -lpthread
  To Run: ./a.out 3 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

struct pthread_sum{
  double *a,sum;
  int N,size;
  long tid;
};

void *compute(void *arg) {
    int myStart, myEnd, myN, i;
    struct pthread_sum thr = (struct pthread_sum) arg;

    // determine start and end of computation for the current thread
    myN = thr->N/thr->size; 
    myStart = thr->tid*myN;
    myEnd = myStart + myN;
    if (thr->tid == (thr->size-1)) myEnd = thr->N;

    // compute partial sum
    double mysum = 0.0;
    for (i=myStart; i<myEnd; i++){
      mysum += thr->a[i];
    }

    // grab the lock, update global sum, and release lock
    thr->sum = mysum;
    return (NULL);
}

int main(int argc, char **argv) {
    long i;
    pthread_t *tid;

    if (argc != 3) {
       printf("Usage: %s <# of elements> <# of threads>\n",argv[0]);
       exit(-1);
    }

    int N = atoi(argv[1]); // no. of elements
    int size = atoi(argv[2]); // no. of threads
     struct pthread_sum *threads = malloc(sizeof(struct pthread_sum) * size); 
    double *a=NULL;
    // allocate vector and initialize
    tid = (pthread_t *)malloc(sizeof(pthread_t)*size);
    a = (double *)malloc(sizeof(double)*N); 
    for (i=0; i<N; i++)
      a[i] = (double)(i + 1);

    // create threads
    for ( i = 0; i < size; i++){
        threads[i].a = a;
        threads[i].N=N;
        threads[i].size=size;
        threads[i].tid=i;
        pthread_create(&tid[i], NULL, compute, (void *)&threads[i]);
    }
    
    // wait for them to complete
    for ( i = 0; i < size; i++)
      pthread_join(tid[i], NULL);
    
    int k=0;
    double sum=0.0;

    for(k=0;k<size;k++){
    sum = sum + threads[k].sum;
    }
    
    printf("The total is %g, it should be equal to %g\n", 
           sum, ((double)N*(N+1))/2);
    
    return 0;
}
