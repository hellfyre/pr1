#include <stdio.h>

#include "measure_processtime.h"

int main(void) {
  unsigned int time[100], time_tmp, time_max;

  measure_init();

  for (int i=0; i<100; i++) {
    measure_start();
    time_tmp = measure_end();
    time[i] = time_tmp;
  }

  time_max = time[0];
  for (int i=0; i<100; i++) {
    printf("%d %d\n", i+1, time[i]);
    if (time[i] > time_max) time_max = time[i];
  }
  printf("max: %d\n", time_max);
}
