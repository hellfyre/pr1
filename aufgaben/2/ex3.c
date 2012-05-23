#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include <measure_processtime.h>

#define N 15

int main(int argc, char **argv) {
  int myRank, commSize;
  int nOpt, rangeStart, rangeEnd;
  long sum = 0;
  static long time = 0;
  //MPI_Status somestatus;

  int *myVector = malloc( sizeof(int) * N );

  measure_init();

  MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    nOpt = N/commSize;
    rangeStart = myRank * nOpt;
    rangeEnd = rangeStart + nOpt;

    if (myRank == 0) {
      for (int i=0; i<N; i++) {
        myVector[i] = rand();
      }
    }
    else if (myRank == (commSize-1)) {
      rangeEnd = N;
    }

    MPI_Bcast(myVector, N, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i=0; i<N; i++) {
      printf("%d: myVector[%d] = %d\n", myRank, i, myVector[i]);
    }
    printf("%d: start=%d, end=%d\n", myRank, rangeStart, rangeEnd);

    for (int i=rangeStart; i<rangeEnd; i++) {
      sum += myVector[i];
    }
    printf("%d: sum=%ld\n", myRank, sum);

  MPI_Finalize();

  free(myVector);
}
