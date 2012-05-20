#include <stdlib.h>
#include <stdio.h>

#include "measure_processtime.h"

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
  printf("%d %ld\n", step, time);

  return sum;
}

int main() {
  static unsigned int S;
  static const int n = 5000000;

  measure_init();
  S = 1;
  
  double *x = malloc(n * sizeof(double));
  init_array(x, n, S);

  some_function(x, n, S);
  for ( S=2; S<=16 ; S+=2 ) {
    some_function(x, n, S);
  }  

}
