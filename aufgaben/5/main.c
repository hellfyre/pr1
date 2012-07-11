#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>
#include <time.h>

#include "drawcircle.h"
#include "planets.h"
#include "bitmap.c"
#include "gettime.c"

#define N         50
#define TIMESTEPS 100
#define STEPSIZE  5

int random_in_range (unsigned int min, unsigned int max) {

  int base_random = rand(); /* in [0, RAND_MAX] */
  if (RAND_MAX == base_random) return random_in_range(min, max);
  /* now guaranteed to be in [0, RAND_MAX) */
  int range       = max - min,
      remainder   = RAND_MAX % range,
      bucket      = RAND_MAX / range;
  /* There are range buckets, plus one smaller interval
     within remainder of RAND_MAX */
  if (base_random < RAND_MAX - remainder) {
    return min + base_random/bucket;
  }
  else {
    return random_in_range (min, max);
  }

}

int main() {
  const double G = -6.673e-11;
  planet *planets = malloc(sizeof(planet)*N);
  color *colors = malloc(sizeof(color)*N);

  srand(time(NULL));

  // randomly generate N planets
  for (int i=0; i<N; i++) {
    int radius = random_in_range(1, RADIUS_MAX-1);
    planets[i].r = radius;
    planets[i].x = random_in_range(radius, FIELD_MAX_X - radius); // generate planets only inside the boundaries of our world
    planets[i].y = random_in_range(radius, FIELD_MAX_Y - radius);
    planets[i].m = radius*20000000000;
    planets[i].vx = random_in_range(0,6) - 3.0;
    planets[i].vy = random_in_range(0,6) - 3.0;

    colors[i].red   = random_in_range(0, 0x100);
    colors[i].green = random_in_range(0, 0x100);
    colors[i].blue  = random_in_range(0, 0x100);
    planets[i].c = &colors[i];
  }

  // sort the planets by their position in x
  qsort(planets, N, sizeof(planet), planet_compare);

  // resolve collisions
  int loops = 0;
  int collisions = 1;
  while (collisions > 0) {

    collisions = 0;
    for (int i=0; i<N-1; i++) {
      for (int j=i+1; j<N; j++) {

        double distance_x = planets[j].x - planets[i].x;
        if ( distance_x > 2 * RADIUS_MAX ) break; // no further collisions can occur

        double radiussum = planets[i].r + planets[j].r;
        if ( distance_x < radiussum ) { // planets collide in x
          if ( fabs(planets[i].y - planets[j].y) < radiussum ) { // planets also collide in y

            collisions = 1;
            if (planets[i].r < planets[j].r) {
              int radius = (int) ceil(planets[i].r);
              planets[i].x = random_in_range(radius, FIELD_MAX_X - radius); // move planet to another (random) location
              planets[i].y = random_in_range(radius, FIELD_MAX_Y - radius);
              break;
            }
            else {
              int radius = (int) ceil(planets[j].r);
              planets[j].x = random_in_range(radius, FIELD_MAX_X - radius); // move planet to another (random) location
              planets[j].y = random_in_range(radius, FIELD_MAX_Y - radius);
            }
          }
        }
      }
    }
    qsort(planets, N, sizeof(planet), planet_compare);

    if (loops == 300) break;
  }

  loops++;

  int myRank, commSize;
  MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);

    memset(image, 0, sizeof(color)*WIDTH*HEIGHT);
    for (int i=0; i<N; i++) {
      dipDrawCircleFill(planets[i].x, planets[i].y, planets[i].r, *planets[i].c);
    }

    char filename[1024];
    saveBMP("images/planets000.bmp", (unsigned char *) image, WIDTH, HEIGHT, 0);

    //timesteps
    reset_time();
    for(int t=0; t<TIMESTEPS; t++) {

      memset(image, 0, sizeof(color)*WIDTH*HEIGHT);

      double fx = 0, fy = 0;
      for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
          if (i == j) continue;
          double dist = sqrt( pow(planets[i].x - planets[j].x,2) + pow(planets[i].y - planets[j].y,2) );
          double fmass = G * planets[i].m * planets[j].m / pow(dist,3);
          fx += fmass * (planets[i].x - planets[j].x);
          fy += fmass * (planets[i].y - planets[j].y);
        }

        // x_k = x_(k-1) + dt * v_(k-1)
        planets[i].x += STEPSIZE * planets[i].vx;
        planets[i].y += STEPSIZE * planets[i].vy;
        if (planets[i].x < 0) planets[i].x += FIELD_MAX_X;
        if (planets[i].y < 0) planets[i].y += FIELD_MAX_Y;
        if (planets[i].x > FIELD_MAX_X) planets[i].x -= FIELD_MAX_X;
        if (planets[i].y > FIELD_MAX_Y) planets[i].y -= FIELD_MAX_Y;

        // v_k = v_(k-1) + dt * a_(k-1)
        planets[i].vx += STEPSIZE * fx/planets[i].m;
        planets[i].vy += STEPSIZE * fy/planets[i].m;

      }

      for (int i=0; i<N; i++) {
        int collision = 0;
        for (int j=i+1; j<N; j++) {
          if(planet_planet_collision(planets[j],planets[i]) > 0){
            collision = 1;
            bewegungsrichtungUmkehren(&planets[j]);
            bewegungsrichtungUmkehren(&planets[i]);

          }
        }
        if (collision) {
          color c;
          c.red = 255;
          c.green = 0;
          c.blue = 0;
          dipDrawCircleFill(planets[i].x, planets[i].y, planets[i].r, c);
        }
        else {
          dipDrawCircleFill(planets[i].x, planets[i].y, planets[i].r, *planets[i].c);
        }
      }

      //save picture of this TIMESTEP
      for (int i=0; i<N; i++) {
        //dipDrawCircleFill(planets[i].x, planets[i].y, planets[i].r, *planets[i].c);
      }

      sprintf(filename, "images/planets%03d.bmp", t+1);
      saveBMP(filename, (unsigned char *) image, WIDTH, HEIGHT, 0);
    }
    double time = get_time();
    printf("Serial: %f seconds\n", time);

  MPI_Finalize();

  return 0;
}
