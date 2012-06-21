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

void solve(double *x, const double *s,
		unsigned int m, unsigned int n,
		unsigned int iterations)
{
    int i, j, it;
    double *x_new = (double*)malloc(sizeof(double)*M*N);
    for (it = 0; it < iterations; it++)
    {
        for (i = 0; i < M; i++)
        {
            for (j = 0; j < N; j++)
            {
                double x_top   = (i < M-1 ? x[(i+1)*N+j] : 0);
                double x_down  = (i > 0   ? x[(i-1)*N+j] : 0);
                double x_left  = (j > 0   ? x[i*N+(j-1)] : 0);
                double x_right = (j < N-1 ? x[i*N+(j+1)] : 0);
                x_new[i*N+j] = (s[i*N+j]+x_top+x_down+x_left+x_right)/4;
            }
        }
        memcpy(x, x_new, M*N*sizeof(double));
    }
    free(x_new);
}

int main(int argc, char **argv)
{
    // Set up problem
    printf("Setting up problem...");
    double *x = (double*)malloc(sizeof(double)*(M*N));
    double *s = (double*)malloc(sizeof(double)*(M*N));
    
    memset(x, (char)0, sizeof(double)*M*N);
    memset(s, (char)0, sizeof(double)*M*N);
    
    int i, j;
    for (i = M/4*N; i < M/2*N; i += N)
        for (j = N/4; j < N/2; j++) s[i+j] = 100;

    printf("ok\n");
       
    printf("Solving...\n");
    resetTime();
    unsigned int iteration;
    for (iteration = 0; iteration < MAX_ITERATIONS; )
    {
        // solve
        solve(x, s, M, N, 100);
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
    
    free(x);
    free(s);

    return 0;
}
