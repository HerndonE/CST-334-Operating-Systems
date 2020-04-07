#include<stdio.h>
#include<stdlib.h>

float round_robin(float *, int);

int main () {
   int num_jobs = 3;
   float jobs1[3] = {3,6,10};
   printf("avg. turnaround = %.2f\n", round_robin(jobs1, num_jobs));

   num_jobs = 0;
   float *jobs2;
   printf("avg. turnaround = %.2f\n", round_robin(jobs2, num_jobs));

   num_jobs = 1;
   float jobs3[1] = {2.3};
   printf("avg. turnaround = %.2f\n", round_robin(jobs3, num_jobs));

   num_jobs = 5;
   float jobs4[5] = {2, 5, 5, 8, 12};
   printf("avg. turnaround = %.2f\n", round_robin(jobs4, num_jobs));

   exit(0);
}

