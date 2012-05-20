#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "measure_processtime.h"

void init_array(long int *array, unsigned int length, unsigned int step) {
  unsigned int i;
  for ( i=0; i<length; i+=step ) {
    array[i] = rand();
  }
}

int main (){
 long int xmax, j;
 long int n = 2,i;
 long int x[1048560];
 static long leTime = 0;
 
 measure_init();
 init_array(x, 1048560, 1);

 for(j=0;j<20;j++){
  measure_start();

  for (xmax = x[0], i = 1; i < n; i++){
       xmax = x[i] < xmax ? xmax : x[i];
  } 
  
 leTime = measure_end();

 printf ("%ld;%ld\n", n, leTime);
 n=n*2;
 }
 return 0;
}
