#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include <measure_processtime.h>

#define N 1000

int main(int argc, char **argv) {
  static int myRank;
  static long time = 0;
  MPI_Status somestatus;

  int *myVector = malloc( sizeof(int) * N );

  measure_init();

  MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    if (myRank == 0) {
      for (i=0; i<N; i++) {
        myVector[i] = rand();
      }
      MPI_Bcast(myVector, N, MPI_INT, 0, MPI_COMM_WORLD);
    }
    else {
      MPI_Bcast(myVector, N, MPI_INT, 0, MPI_COMM_WORLD);
    }

  MPI_Finalize();

}
