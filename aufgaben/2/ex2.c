#include <stdio.h>
#include <unistd.h>
#include <mpi.h>

#include <measure_processtime.h>

int main(int argc, char **argv) {
  static int local_rank = -1;
  static long time = 0;

  measure_init();

  MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &local_rank);

    if ( local_rank == 0 ) {
      usleep(100000); // sleep for 100ms to make sure the MPI_Receive on the other side is ready
      measure_start();
      MPI_Send();
      MPI_Receive();
      time = measure_end();
      printf("Process %d received %s.\n", local_rank);
    }
    else {
      MPI_Receive();
      MPI_Send();
    }

  MPI_Finalize();

}
