#include <stdio.h>
#include <string.h>

void setupProblem(double *A, double *b, unsigned int m, unsigned int n)
{
    memset(A, (char)0, sizeof(double)*(m*n)*(m*n));
    memset(b, (char)0, sizeof(double)*(m*n));
    
    int i, j;
    for (i = 0;   i < (m*n)*(m*n); i += m*n+1) A[i] = 4;
    for (i = 1;   i < (m*n)*(m*n); i += m*n+1) A[i] = -1;
    for (i = m*n; i < (m*n)*(m*n); i += m*n+1) A[i] = -1;
    for (i = n;   i < (m*n)*((m-1)*n); i += m*n+1) A[i] = -1;
    for (i = m*m*n;   i < (m*n)*(m*n); i += m*n+1) A[i] = -1;
    
    for (i = (n-1)*(m*n+1)+1;   i < (m*n)*(m*n); i += n*(m*n+1)) A[i] = 0;
    for (i = (n-1)*(m*n+1)+m*n; i < (m*n)*(m*n); i += n*(m*n+1)) A[i] = 0;
    
    for (i = m/4*n; i < m/2*n; i += n)
        for (j = n/4; j < n/2; j++) b[i+j] = 100;
}

void printMatrixToFile(const char *pathToFile, const double *x,
                       unsigned int m, unsigned int n)
{
    FILE *file = fopen(pathToFile, "w");
    
    int i, j;
    for (i = 0; i < (m*n); i++)
    {
        for (j = 0; j < (m*n); j++)
        {
            fprintf(file, "%2d ", (int)x[i*(m*n)+j]);
        }
        fprintf(file, "\n");
    }
    
    fclose(file);
}

