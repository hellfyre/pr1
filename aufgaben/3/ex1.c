#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv) {
  int local_rank = -1;

  MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &local_rank);
    printf("Hello World! Greetings from process %d.\n", local_rank);

  MPI_Finalize();

}
