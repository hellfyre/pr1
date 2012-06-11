#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

#include <sys/time.h>

#include <gettime.c>

int main(int argc, char **argv) {
  int myRank, commSize;
  int n, nOpt, rest;
  int *sendcnts, *displacement;
  double *v1, *v2;
  double subproduct = 0;
  double recvBuff;
  double *v1_recv, *v2_recv;
  static double time = 0.0;
  MPI_Status status;

  n = pow(10, atoi(argv[1]));

  struct timeval time_seed;
  gettimeofday(&time_seed, NULL);
  srand(time_seed.tv_sec);

  MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    nOpt = n/commSize;
    rest = n - nOpt * commSize;

    sendcnts = malloc(sizeof(int)*commSize);
    displacement = malloc(sizeof(int)*commSize);

    displacement[0] = 0;
    for (int i=0; i<commSize; i++) {
      sendcnts[i] = nOpt;
      if (i>0) displacement[i] = displacement[i-1] + sendcnts[i-1]; // * sizeof(double);
      if (rest>0) {
        sendcnts[i]++;
        rest--;
      }
    }

    v1_recv = malloc(sizeof(double) * sendcnts[myRank]);
    v2_recv = malloc(sizeof(double) * sendcnts[myRank]);
    if (myRank == 0) {
      v1 = malloc(sizeof(double) * n);
      v2 = malloc(sizeof(double) * n);
      for (int i=0; i<n; i++) {
        v1[i] = rand();
        v2[i] = rand();
      }
      printf("\n\n");
      printf("job: n=%d p=%d\n", n, commSize);
      printf("rank  time  gflops  scalar\n\n");
    }
    else v1 = v2 = NULL;

    MPI_Barrier(MPI_COMM_WORLD);
    resetTime();
      MPI_Scatterv(v1, sendcnts, displacement, MPI_DOUBLE, v1_recv, sendcnts[myRank], MPI_DOUBLE, 0, MPI_COMM_WORLD);
      MPI_Scatterv(v2, sendcnts, displacement, MPI_DOUBLE, v2_recv, sendcnts[myRank], MPI_DOUBLE, 0, MPI_COMM_WORLD);

      for (int i=0; i<sendcnts[myRank]; i++) {
        subproduct += v1_recv[i] * v2_recv[i]; // 2*sendcnts[myRank] Flops
      }

      for (int i=2; i<=commSize; i*=2) {
        for (int j=commSize/i; j>0; j--) {
          int offset = commSize - i*j;
          for (int k=0; k<i/2; k++) {
            int proc1 = offset + k;
            int proc2 = proc1 + i/2;
            if (myRank == proc1) {
              MPI_Send(&subproduct, 1, MPI_DOUBLE, proc2, 0, MPI_COMM_WORLD);
              MPI_Recv(&recvBuff, 1, MPI_DOUBLE, proc2, 0, MPI_COMM_WORLD, &status);
              subproduct += recvBuff;
            }
            if (myRank == proc2) {
              MPI_Recv(&recvBuff, 1, MPI_DOUBLE, proc1, 0, MPI_COMM_WORLD, &status);
              MPI_Send(&subproduct, 1, MPI_DOUBLE, proc1, 0, MPI_COMM_WORLD);
              subproduct += recvBuff;
            }
          }
        }
      }

    MPI_Barrier(MPI_COMM_WORLD);
    time = getTime();

    int loopFlops = 0;
    for (int i=2; i<=commSize; i*=2) {
      loopFlops++;
    }
    double gflops = ( (2*sendcnts[myRank]) + (loopFlops) ) / ( time * 1000000000 );

    printf("%d %f %f %f\n", myRank, time, gflops, subproduct);

    free(v1);
    free(v2);
    free(v1_recv);
    free(v2_recv);
    free(sendcnts);
    free(displacement);

  MPI_Finalize();

}
