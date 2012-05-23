#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include <measure_processtime.h>

#define N 1000 * 1000 * 10

int main(int argc, char **argv) {
  long overall_sum = 0;
  static long time = 0;

  measure_init();

  int *myVector = malloc( sizeof(int) * N );

  MPI_Init(&argc, &argv);

    for (int i=0; i<N; i++) {
      myVector[i] = rand();
    }

    measure_start();
    for (int i=0; i<N; i++) {
      overall_sum += myVector[i];
    }
    time = measure_end();

    printf("time=%ld\n", time);

  MPI_Finalize();

  free(myVector);
}
