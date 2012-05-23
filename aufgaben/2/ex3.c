#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include <measure_processtime.h>

#define N 15

int main(int argc, char **argv) {
  int myRank, commSize;
  int nOpt, rangeStart, rangeEnd;
  long overall_sum = 0;
  static long time = 0;

  measure_init();

  MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    nOpt = N/commSize;
    rangeStart = myRank * nOpt;
    rangeEnd = rangeStart + nOpt;

    int *myVector = malloc( sizeof(int) * N );
    long *sum = malloc( sizeof(long) * commSize );
    sum[myRank] = 0;

    if (myRank == 0) {
      for (int i=0; i<N; i++) {
        myVector[i] = rand();
      }
    }
    else if (myRank == (commSize-1)) {
      rangeEnd = N;
    }

    MPI_Bcast(myVector, N, MPI_INT, 0, MPI_COMM_WORLD);

    measure_start();
    for (int i=rangeStart; i<rangeEnd; i++) {
      sum[myRank] += myVector[i];
    }

    MPI_Allgather(&sum[myRank], 1, MPI_LONG, sum, 1, MPI_LONG, MPI_COMM_WORLD);

    for (int i=0; i<commSize; i++) {
      overall_sum += sum[i];
    }

    MPI_Barrier(MPI_COMM_WORLD);
    time = measure_end();

    printf("%d: time=%ld\n", myRank, time);

  MPI_Finalize();

  free(myVector);
  free(sum);
}
