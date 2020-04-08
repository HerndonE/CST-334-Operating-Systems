
/* 
 * A simple pthreads program in which two threads produce data
 * and a third thread consumes and merges the data.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

// state variables
// the merging process puts -1 in a buffer to indicate the buffer is empty
// a writing process puts -2 in a buffer to indicate no more data will be provided
int abuf, bbuf;

// synchronization variables
// the merging process signals ready_awrite when it has read a value from buffer a
// the merging process signals ready_bwrite when it has read a value from buffer b
// a writing process signals ready_read  when it has written a value into the buffer
pthread_cond_t ready_awrite, ready_bwrite, ready_read;
pthread_mutex_t lock;


// write data into buffer a when it is empty
void *writer_a(void *arg) {
   int *data = (int *)arg;

   int i = 0;
   while (data[i] >= 0) {
      pthread_mutex_lock(&lock);
      // wait for abuf to be empty
      while (abuf >= 0) {
         pthread_cond_wait(&ready_awrite, &lock);
      }
      // write a value into abuf
      abuf = data[i];
      pthread_cond_signal(&ready_read);
      pthread_mutex_unlock(&lock);
      i++;
   }

   // input data is finished, so write -2 into abuf
   pthread_mutex_lock(&lock);
   while (abuf >= 0) {
      pthread_cond_wait(&ready_awrite, &lock);
   }
   abuf = -2;	
   pthread_cond_signal(&ready_read);
   pthread_mutex_unlock(&lock);
}


// write data into buffer b when it is empty
void *writer_b(void *arg) {
   int *data = (int *)arg;

   int i = 0;
   while (data[i] >= 0) {
      pthread_mutex_lock(&lock);
      while (bbuf >= 0) {
         pthread_cond_wait(&ready_bwrite, &lock);
      }
      bbuf = data[i];
      pthread_cond_signal(&ready_read);
      pthread_mutex_unlock(&lock);
      i++;
   }

   pthread_mutex_lock(&lock);
   while (bbuf >= 0) {
      pthread_cond_wait(&ready_bwrite, &lock);
   }
   bbuf = -2;
   pthread_cond_signal(&ready_read);
   pthread_mutex_unlock(&lock);
}


//
// print data from either buffer when it is available;
// the output will be sorted if the data written to each buffer is sorted
void *merger(void *arg) {
  while (true) {
    pthread_mutex_lock(&lock);

    // there are four cases:
    // 1. if -2 is in both buffers, then we're finished.
    // 2. if >= 0 in both buffers, then read and print the smaller
    //    of the two values.
    // 3. if >= 0 in one buffer and -2 in the other buffer, then
    //    then read and print the value that is >= 0
    // 4. if value -1 in either buffer, then wait for more data to arrive
 
if (abuf < bbuf && abuf >= 0 && bbuf >= 0) {
   printf("%d\n", abuf);
   abuf = -1;
   pthread_cond_signal( &ready_awrite);
 } else if (bbuf < abuf && bbuf >= 0 && abuf >= 0) {
   printf("%d\n", bbuf);
   bbuf = -1;
   pthread_cond_signal( &ready_bwrite);
 } else if (abuf >= 0 && bbuf == -2) {
   printf("%d\n", abuf);
   abuf = -1;
   pthread_cond_signal( &ready_awrite);
 } else if (bbuf >= 0 && abuf == -2) {
   printf("%d\n", bbuf);
   bbuf = -1;
   pthread_cond_signal( &ready_bwrite);
 } else if (abuf >= 0 && bbuf >= 0 && abuf == bbuf) {
   printf("%d\n", abuf);
   abuf = -1;
   pthread_cond_signal( &ready_awrite);
 }
 
    pthread_mutex_unlock(&lock);
  }
}
      

int main() {

  // read data for arrays adat, bdat from standard input
  // line 1: number of values on lines 2,3
  // line 2: values for array adat
  // line 3: values for array bdat
  // The values on lines 2 and 3 must not be negative.
  // After reading the data a value of -1 is added to the end of adat, bdat.

  int na, nb;
  if (scanf("%d %d", &na, &nb) != 2) {
    printf("error: na,nb not provided\n");
    exit(1);
  }

  int adat[na+1];
  int bdat[nb+1];
  int i;
  for (i = 0; i < na; i++) {
    scanf("%d", &adat[i]);
  }
  adat[i] = -1;
  for (i = 0; i < nb; i++) {
    scanf("%d", &bdat[i]);
  }
  bdat[i] = -1;

  // initialize state variables (both buffers initially empty)
  abuf = -1;
  bbuf = -1;

  // initialize synchronization variables
  pthread_mutex_init(&lock, NULL);
  pthread_cond_init(&ready_read, NULL);
  pthread_cond_init(&ready_awrite, NULL);
  pthread_cond_init(&ready_bwrite, NULL);

  // create threads
  pthread_t p1, p2, p3;
  pthread_create(&p1, NULL, writer_a, (void *)adat);
  pthread_create(&p2, NULL, writer_b, (void *)bdat);
  pthread_create(&p3, NULL, merger, NULL);

  // wait for threads to finish
  pthread_join(p1, NULL);
  pthread_join(p2, NULL);
  pthread_join(p3, NULL);

  return 0;
}
