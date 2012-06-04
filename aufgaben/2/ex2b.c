#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include <measure_processtime.h>

int main(int argc, char **argv) {
  static int local_rank = -1;
  static long time = 0;

  int i, curr_size, curr_byte;
  double curr_rate;
  int max_elements = 1000 * 100;
  int *foobar = malloc( sizeof(int) * max_elements);
  for (i=0; i<max_elements; i++) {
    foobar[i] = 42;
  }
  MPI_Status somestatus;

  measure_init();

  MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &local_rank);

    if ( local_rank == 0 ) {
      for (i=1; i<=25; i++) {
        curr_size = 1000 * i;
        //printf("i: %d curr_size: %d\n", i, curr_size);
        MPI_Barrier(MPI_COMM_WORLD);
        measure_start();
        MPI_Send(foobar, curr_size, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(foobar, curr_size, MPI_INT, 1, 0, MPI_COMM_WORLD, &somestatus);
        time = measure_end();
        curr_byte = (curr_size*4); //byte
        curr_rate = (curr_byte / (double) time) * 1000; // byte/ns * 1000ns/us == byte/us == Mbyte/s
        printf("%d %f\n", curr_byte/1000, curr_rate); // print kbyte, Mbyte/s
      }
    }
    else {
      for (i=1; i<=25; i++) {
        curr_size = 1000 * i;
        MPI_Barrier(MPI_COMM_WORLD);
        MPI_Recv(foobar, curr_size, MPI_INT, 0, 0, MPI_COMM_WORLD, &somestatus);
        MPI_Send(foobar, curr_size, MPI_INT, 0, 0, MPI_COMM_WORLD);
      }
    }

  MPI_Finalize();

}
