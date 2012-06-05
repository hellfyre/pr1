#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

#include <sys/time.h>

#include <gettime.c>

int main(int argc, char **argv) {
  int myRank, commSize;
  int N, nOpt, rangeStart, rangeEnd;
  double *v1, *v2, *subproduct;
  double scalar = 0;
  static double time = 0.0;

  struct timeval time_seed;
  gettimeofday(&time_seed, NULL);
  srand(time_seed.tv_sec);
  measure_init();

  N = pow(10, atoi(argv[1]));

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
    subproduct = malloc(sizeof(double) * commSize);
    subproduct[myRank] = 0;
    if (myRank == 0) {
      for (int i=0; i<N; i++) {
        v1[i] = rand();
        v2[i] = rand();
      }
      printf("\n\n");
      printf("job: n=%d p=%d\n", N, commSize);
      printf("rank  time  gflops  scalar\n\n");
    }

    MPI_Barrier(MPI_COMM_WORLD);
    resetTime();
      MPI_Bcast(v1, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
      MPI_Bcast(v2, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

      for (int i=rangeStart; i<rangeEnd; i++) {
        subproduct[myRank] += v1[i] * v2[i]; // 2*(rangeEnd-rangeStart) Flops
      }

      MPI_Allgather(&subproduct[myRank], 1, MPI_DOUBLE, subproduct, 1, MPI_DOUBLE, MPI_COMM_WORLD);

      for (int i=0; i<commSize; i++) {
        scalar += subproduct[i]; // commSize Flops
      }
    MPI_Barrier(MPI_COMM_WORLD);
    time = getTime();

    double gflops = ( (2*(rangeEnd-rangeStart)) + (commSize) ) / (time * 1000000000);

    printf("%d %ld %f %f\n", myRank, time, gflops, scalar);

    free(v1);
    free(v2);
    free(subproduct);

  MPI_Finalize();

}
