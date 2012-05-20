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
  printf("%d %ld\n", length, time);

  return sum;
}

int main(int argc, char *argv[]) {
  const char *spec_n_str = argv[1];
  const int n = atoi(spec_n_str);

  measure_init();

  double *x = malloc(n * sizeof(double));
  init_array(x, n, 1);
  some_function(x, n, 1);

}
