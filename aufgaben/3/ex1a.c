#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include <sys/time.h>

#include <measure_processtime.h>

int main(int argc, char **argv) {
  int local_rank = -1;
  double *v1, *v2;
  double scalar = 0;
  unsigned int n = 1000, n_max = 10000000;
  static unsigned long time = 0;

  struct timeval time_seed;
  gettimeofday(&time_seed, NULL);
  srand(time_seed.tv_sec);
  measure_init();

  MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &local_rank);

    printf("n   scalar   time   GFlops\n");

    for (n=10; n<=n_max; n*=10) {
      v1 = malloc(sizeof(double) * n);
      v2 = malloc(sizeof(double) * n);
      for (int i=0; i<n; i++) {
        v1[i] = rand();
        v2[i] = rand();
      }

      measure_start();
      for (int i=0; i<n; i++) {
        scalar += v1[i] * v2[i]; // 2*n Flops
      }
      time = measure_end();
      double time_double = (double) time;

      printf("%d %f %ld %f\n", n, scalar, time, ((2*n)/time_double));
      free(v1);
      free(v2);
    }

  MPI_Finalize();

}
