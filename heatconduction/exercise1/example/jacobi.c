#include <math.h>
#include <stdlib.h>

/*
 Computes a solution x for the linear equation system Ax=b.
 The solution will be computed iteratively using the Jacobi method.
 
 Parameters:
    [in]     A              - an nxn system matrix (row-wise)
    [in]     b              - right hand side (n-dim vector)
    [in/out] x              - startvector at beginning, solution after computation
    [in]     n              - dimension
    [in]     maxIterations  - max. number of iterations to compute before abort
    [in]     tolerance      - min. change of solution without abort
 
 Returns:
    number of iterations actually computed
 */
unsigned int jacobi_solve(const double *A,
                    const double *b,
                    double *x,
                    const unsigned int n,
                    const unsigned int maxIterations,
                    const double tolerance)
{
    double *xNew = (double*)malloc(sizeof(double)*n);
    double change;
    
    int iterations, i, j;
    for (iterations = 0; iterations < maxIterations; iterations++)
    {
        for (i = 0; i < n; i++)
        {
            xNew[i] = 0.;
            for (j = 0; j < n; j++)
            {
                if (j != i)
                    xNew[i] += A[i*n+j]*x[j];
            }
            xNew[i] = (b[i]-xNew[i])/A[i*n+i];
        }
        for (i = 0, change = 0.; i < n; i++)
        {
            change += fabs(xNew[i]-x[i]);
            x[i] = xNew[i];
        }
        if (change <= tolerance) break;
    }
    
    free(xNew);
    return iterations;
}
