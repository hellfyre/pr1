#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include <sys/time.h>

#include <measure_processtime.h>

#define N 1000 * 1000 * 10

int main(int argc, char **argv) {
  int myRank, commSize;
  int nOpt, rangeStart, rangeEnd;
  double *v1, *v2;
  double subproduct = 0;
  double scalar = 0;
  double receiveBuff;
  static unsigned long time = 0;
  MPI_Status status;

  struct timeval time_seed;
  gettimeofday(&time_seed, NULL);
  srand(time_seed.tv_sec);
  measure_init();

  MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    nOpt = N/commSize;
    rangeStart = myRank * nOpt;
    rangeEnd = rangeStart + nOpt;

    if (myRank == (commSize-1)) {
      rangeEnd = N;
    }

    v1 = malloc(sizeof(double) * N);
    v2 = malloc(sizeof(double) * N);
    if (myRank == 0) {
      for (int i=0; i<N; i++) {
        v1[i] = rand();
        v2[i] = rand();
      }
      printf("\n\n");
      printf("job: n=%d p=%d\n", N, commSize);
      printf("rank  time  gflops  scalar\n\n");
    }

    measure_start();
      MPI_Bcast(v1, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
      MPI_Bcast(v2, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

      for (int i=rangeStart; i<rangeEnd; i++) {
        subproduct += v1[i] * v2[i]; // 2*(rangeEnd-rangeStart) Flops
      }

      for (int i=2; i<=commSize; i*=2) {
        if (myRank % i == 0) {
          if ( (myRank+i/2) < commSize ) {
            MPI_Recv(&receiveBuff, 1, MPI_DOUBLE, myRank+(i/2), 0, MPI_COMM_WORLD, &status);
            subproduct += receiveBuff; // 1 Flop per loop
          }
        }
        else {
          MPI_Send(&subproduct, 1, MPI_DOUBLE, myRank-(i/2), 0, MPI_COMM_WORLD);
          break;
        }
      }

      MPI_Bcast(&subproduct, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    time = measure_end();

    int loopFlops = 0;
    for (int i=2; i<=commSize; i*=2) {
      if (myRank % i == 0) loopFlops++;
    }
    double time_double = (double) time;
    double gflops = ( (2*(rangeEnd-rangeStart)) + (loopFlops) ) / time_double;

    printf("%d %ld %f %f\n", myRank, time, gflops, scalar);

    free(v1);
    free(v2);

  MPI_Finalize();

}
