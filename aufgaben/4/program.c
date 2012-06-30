#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ### Problem Specifications ### */

#define M               1024    // Number of discrete points in Y-direction
#define N               1024    // Number of discrete points in X-direction
#define MAX_ITERATIONS  10000   // Max. number of iterations to compute

/* ### External Interfaces ### */

extern int saveBMP(const char* pathToFile, unsigned char *pixeldata, 
                   unsigned int width, unsigned int height, int invertY);

extern void visualizeMap(const double *map, unsigned char /*retain*/ **pixels,
                  unsigned int n);

extern void resetTime();
extern double getTime();

/* ### Implementation ### */

struct area {
  double *v;
  int x;
  int y;
  int x_size;
  int y_size;
  int n;
  int m;
};

void divide(double *v, struct area *a, int myRank, int P, int n, int m) {
  int old = 1;
  int x, y;
  // sinnvolle Aufteilung auf P Prozessoren finden
  for (int i=1; i<=P; i++) {
    if (P%i == 0) {
      int j = P/i;
      if ( (i==j) || (j==old) ) {
        x = i;
        y = j;
        break;
      }
      else {
        old = i;
      }
    }
  }

  int x_opt = n/x;
  int y_opt = m/y;
  int x_rest = n - x*x_opt;
  int y_rest = m - y*y_opt;
  int x_sizes[x];
  int y_sizes[y];

  for (int i=0; i<x; i++) {
    x_sizes[i] = x_opt;
    if (x_rest > 0) {
      x_sizes[i]++;
      x_rest--;
    }
  }
  for (int i=0; i<y; i++) {
    y_sizes[i] = y_opt;
    if (y_rest > 0) {
      y_sizes[i]++;
      y_rest--;
    }
  }

  // Informationen zum eigenen Gebiet sammeln
  a->x = myRank % x;
  a->y = myRank / x;
  a->x_size = x_sizes[a->x];
  a->y_size = y_sizes[a->y];
  a->n = x;
  a->m = y;

  // Gebiete erzeugen
  int *areas[x*y];
  int areacounter = 0;
  int y_offset = 0;

  for (int y_koord=0; y_koord<y; y_koord++) {
    int x_offset = y_offset;
    for (int x_koord=0; x_koord<x; x_koord++) {

      int row_upper_bound = y_sizes[y_koord];
      int column_upper_bound = x_sizes[x_koord];
      int areasize = row_upper_bound * column_upper_bound;
      areas[areacounter] = malloc(areasize*sizeof(double));
      int *current_area = areas[areacounter];
      int area_element_counter = 0;
      int area_offset = x_offset;

      for (int row=0; row<row_upper_bound; row++) {
        for (int column=0; column<column_upper_bound; column++) {
          current_area[area_element_counter] = v[column+area_offset];
          area_element_counter++;
        }
        area_offset += n;
      }
      x_offset+=x_sizes[x_koord];
      areacounter++;
    }
    y_offset += n * y_sizes[y_koord];
  }

  a->v = areas[myRank];

}

void solve(double *x, const double *s,
		unsigned int m, unsigned int n,
		unsigned int iterations)
{
    int i, j, it;
    double *x_new = (double*)malloc(sizeof(double)*m*n);
    for (it = 0; it < iterations; it++)
    {
        double ghost_top[n];
        double ghost_bottom[n];
        double ghost_left[m];
        double ghost_right[m];
        memset(ghost_top, 0, n*sizeof(double));
        memset(ghost_bottom, 0, n*sizeof(double));
        memset(ghost_left, 0, m*sizeof(double));
        memset(ghost_right, 0, m*sizeof(double));

        if ( a->x > 0 ) {
          double left[m];
          int offset = 0;
          for (int i=0; i<m; i++) {
            left[i] = s[offset];
            offset += n;
          }
          MPI_Sendrecv(left, m, MPI_DOUBLE, myRank - 1, 0, ghost_left, m, MPI_DOUBLE, myRank - 1, 0, MPI_COMM_WORLD, NULL);
        }
        else if ( a->x < (a->n-1) ) {
          double right[a->y_size];
          int offset = a->x_size-1;
          for (int i=0; i<a->y_size; i++) {
            right[i] = s[offset];
            offset += a->x_size;
          }
          MPI_Sendrecv(right, m, MPI_DOUBLE, myRank + 1, 0, ghost_right, m, MPI_DOUBLE, myRank + 1, 0, MPI_COMM_WORLD, NULL);
        }
        if ( a->y > 0 ) {
          double top[a->x_size];
          for (int i=0; i<a->x_size; i++) {
            top[i] = s[i];
          }
          MPI_Sendrecv(top, n, MPI_DOUBLE, myRank - n, 0, ghost_top, n, MPI_DOUBLE, myRank - n, 0, MPI_COMM_WORLD, NULL);
        }
        else if ( a->y < (a->m-1) ) {
          double bottom[a->x_size];
          int offset = a->x_size * (a->y_size - 1);
          for (int i=0; i<a->x_size; i++) {
            bottom[i] = s[offset + i];
          }
          MPI_Sendrecv(bottom, n, MPI_DOUBLE, myRank + n, 0, ghost_bottom, n, MPI_DOUBLE, myRank + n, 0, MPI_COMM_WORLD, NULL);
        }

        for (i = 0; i < m; i++)
        {
            for (j = 0; j < n; j++)
            {
                double x_top   = (i < m-1 ? x[(i+1)*n+j] : ghost_top[j]);
                double x_down  = (i > 0   ? x[(i-1)*n+j] : ghost_bottom[j]);
                double x_left  = (j > 0   ? x[i*n+(j-1)] : ghost_left[i]);
                double x_right = (j < n-1 ? x[i*n+(j+1)] : ghost_right[i]);
                x_new[i*n+j] = (s[i*n+j]+x_top+x_down+x_left+x_right)/4;
            }
        }
        memcpy(x, x_new, m*n*sizeof(double));
    }
    free(x_new);
}

int main(int argc, char **argv)
{
    // Set up problem
    printf("Setting up problem...");
    //double *x = (double*)malloc(sizeof(double)*(M*N));
    double *s = (double*)malloc(sizeof(double)*(M*N));
    
    //memset(x, (char)0, sizeof(double)*M*N);
    memset(s, (char)0, sizeof(double)*M*N);
    
    int myRank, commSize;
    MPI_Init(&argc, &argv);

      MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
      MPI_Comm_size(MPI_COMM_WORLD, &commSize);

      int i, j;
      for (i = M/4*N; i < M/2*N; i += N)
          for (j = N/4; j < N/2; j++) s[i+j] = 100;

      printf("ok\n");

      printf("Solving...\n");
      resetTime();

      struct area a;
      divide(s, &a, commSize, N, M);
      double *result_area = (double*) malloc(a.x_size*a.y_size*sizeof(double));

      unsigned int iteration;
      for (iteration = 0; iteration < MAX_ITERATIONS; )
      {
          // solve
          //solve(x, s, M, N, 100);
          solve(result_area, a.v, a.y_size, a.x_size, 100);
          iteration += 100;
          printf("iterations: %d\n", iteration);

          // visualize
          unsigned char *pixels;
          visualizeMap(x, &pixels, M*N);

          // save bitmap
          printf("Saving bitmap...");
          char filename[64];
          sprintf(filename, "images/heatmap%d.bmp", iteration);
          if (!saveBMP(filename, pixels, M, N, 0))
          {
              printf("fail!\n");
              return 1;
          }
          else
          {
              printf("ok\n");
          }
          free(pixels);
      }
      double timeNeededForSolving = getTime();
      printf("End of computation!\nTime needed for solving: %fs\n", timeNeededForSolving);

    MPI_Finalize();

    free(x);
    free(s);

    return 0;
}
