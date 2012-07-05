#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>

#include "drawcircle.h"
#include "planets.h"
#include "bitmap.c"

#define N 100

int main() {
  planet *planets = malloc(sizeof(planet)*N);
  color *colors = malloc(sizeof(color)*N);
  
  struct timeval time_seed;
  gettimeofday(&time_seed, NULL);
  srand(time_seed.tv_sec);

  // randomly generate N planets
  for (int i=0; i<N; i++) {
    int radius = rand() % (8 - 1) + 1; // radius shouldn't be greater than 1/8th of FIELD_MAX_X
    planets[i].r = radius;
    planets[i].x = rand() % (FIELD_MAX_X - 2*radius) + radius; // generate planets only inside the boundaries of our world
    planets[i].y = rand() % (FIELD_MAX_Y - 2*radius) + radius;
    planets[i].m = rand();
    planets[i].vx = rand();
    planets[i].vy = rand();

    colors[i].red   = rand() % 0x100;
    colors[i].green = rand() % 0x100;
    colors[i].blue  = rand() % 0x100;

    /*
    printf("%d: r=%f x=%f y=%f m=%f vx=%f vy=%f rgb=%x%x%x\n",
            i,
            planets[i].r,
            planets[i].x,
            planets[i].y,
            planets[i].m,
            planets[i].vx,
            planets[i].vy,
            colors[i].red,
            colors[i].green,
            colors[i].blue);
    */
  }

  // sort the planets by their position in x
  qsort(planets, N, sizeof(planet), planet_compare);

  for (int i=0; i<N; i++) {
    printf("%d: r=%f x=%f y=%f m=%f vx=%f vy=%f rgb=%x%x%x\n",
            i,
            planets[i].r,
            planets[i].x,
            planets[i].y,
            planets[i].m,
            planets[i].vx,
            planets[i].vy,
            colors[i].red,
            colors[i].green,
            colors[i].blue);

    //dipDrawCircleFill(planets[i].x, planets[i].y, planets[i].r, colors[i]);
  }

  //saveBMP("circles.bmp", (unsigned char *) image, WIDTH, HEIGHT, 0);

  return 0;
}
