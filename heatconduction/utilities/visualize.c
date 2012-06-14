#include <stdlib.h>
#include <float.h>

void visualizeMap(const double *map, unsigned char /*retain*/ **pixels,
                  unsigned int n)
{
    // find minimum, maximum and spread
    int i;
    double min = DBL_MAX, max = DBL_MIN;
    for (i = 0; i < n; i++)
    {
        double value = map[i];
        if (value < min) min = value;
        if (value > max) max = value;
    }
    double spread = max - min;
    
    // allocate pixels
    *pixels = (unsigned char*)malloc(sizeof(unsigned char)*n*3);
    
    // color pixels
    for (i = 0; i < n; i++)
    {
        double relValue = (map[i]-min)/spread;
        (*pixels)[i*3+0] = (char)(255*(1-relValue));
        (*pixels)[i*3+1] = 0;
        (*pixels)[i*3+2] = (char)(255*relValue);
    }
}
