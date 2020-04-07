#include<stdio.h>
#include<stdlib.h>

// return the average turnaround time under round robin
// scheduling with a very short quantum
//
// Values in array jobs must be non-negative and in
// increasing order, else result is undefined.
float round_robin(float * jobs, int num_jobs) {
  int i, j, e;
  float overallTime = 0;
  float turnAroundTime[num_jobs];

  if (num_jobs == 0) {
    return 0;
  }

  e = num_jobs;

  for (i = 0; i < num_jobs; i++) {
    turnAroundTime[i] = 0;
  }

  for (i = 0; i < e; i++) {
    if (i > 0) {
      turnAroundTime[i] += turnAroundTime[i - 1] + (jobs[i] * num_jobs);
    } else {
      turnAroundTime[i] += (jobs[i] * num_jobs);
    }

    for (j = i + 1; j < e; j++) {
      jobs[j] -= jobs[i];
    }
    num_jobs--;
  }

  for (i = 0; i < e; i++) {
    overallTime += turnAroundTime[i];
  }

  overallTime = overallTime / e;
  return overallTime;
}