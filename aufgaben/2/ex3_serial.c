#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include <measure_processtime.h>

#define N 1000 * 1000 * 10

int main(int argc, char **argv) {
  int myRank, commSize;
  long overall_sum = 0;
  static long time = 0;

  measure_init();

  MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);

    int *myVector = malloc( sizeof(int) * N );
    long *sum = malloc( sizeof(long) * commSize );
    sum[myRank] = 0;

    if (myRank == 0) {
      for (int i=0; i<N; i++) {
        myVector[i] = rand();
      }
    }

    measure_start();
    for (int i=0; i<N; i++) {
      sum[myRank] += myVector[i];
    }
    time = measure_end();

    printf("%d: time=%ld\n", myRank, time);

  MPI_Finalize();

  free(myVector);
  free(sum);
}
