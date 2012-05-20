#include <stdlib.h>
#include <stdio.h>

#include "measure_processtime.h"

#define LOWER_BOUND 1000
#define UPPER_BOUND 100000000

void init_array(double *array, unsigned int length, unsigned int step) {
  unsigned int i;
  for ( i=0; i<length; i+=step ) {
    array[i] = rand();
  }
}

double some_function(double *array, unsigned int length, unsigned int step) {
  double sum;
  unsigned int i;
  long time;

  measure_start();
  for ( sum = 0., i = 0; i<length; i += step ) {
    sum += array[i];
  }
  time = measure_end();
  printf("%d %ld\n", length, time);

  return sum;
}

int main() {
  unsigned int n, S, S_n;

  measure_init();
  S = 1000;
  S_n = 1000;
  
  double *x = malloc(UPPER_BOUND * sizeof(double));
  init_array(x, UPPER_BOUND, S);

  some_function(x, 100, S);
  for ( n=LOWER_BOUND; n<=UPPER_BOUND ; n+=S_n ) {
    some_function(x, n, S);
  }  

}
