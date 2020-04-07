#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "mythreads.h"
 
typedef struct { 
   // state var
   long cnt;
   int value; 
   // sync var
   pthread_mutex_t lock;
} COUNTER;

COUNTER *cnt_create() {
  COUNTER *cntr = (COUNTER *)malloc(sizeof(COUNTER));
 
 cntr->value=0;
 pthread_mutex_init(&cntr->lock,NULL);

  return cntr;
}

void cnt_incr(COUNTER *cntr) {
pthread_mutex_lock(&cntr->lock);
cntr->value++;
pthread_mutex_unlock(&cntr->lock);
}

void cnt_decr(COUNTER *cntr) {
pthread_mutex_lock(&cntr->lock);
cntr->value--;
pthread_mutex_unlock(&cntr->lock);
}

long cnt_get(COUNTER *cntr) {
pthread_mutex_lock(&cntr->lock);
int temp = cntr->value;
pthread_mutex_unlock(&cntr->lock);
return temp;
}

/*
 * counting application
 */

void *mythread(void *arg) {
   COUNTER *cntr = (COUNTER *)arg;
   int i;
   for (i = 0; i < 1e7; i++) {
      cnt_incr(cntr);   
   }
   return NULL;
}

int main(int argc, char *argv[]) {
   COUNTER *cntr = cnt_create();

   pthread_t p1, p2;
   printf("main: begin (counter = %ld)\n", cnt_get(cntr));
   Pthread_create(&p1, NULL, mythread, cntr);
   Pthread_create(&p2, NULL, mythread, cntr);

   // join waits for the threads to finish
   Pthread_join(p1, NULL);
   Pthread_join(p2, NULL);
   printf("main: done with both (counter = %ld)\n", cnt_get(cntr));
   return 0;
}

