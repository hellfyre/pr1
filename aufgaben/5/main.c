#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>
#include <time.h>

#include "drawcircle.h"
#include "planets.h"
#include "bitmap.c"

#define N         10
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
			//printf("Mass[%d]: %f \n", i, planets[i].m);
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
    /*
    printf("%dth while loop\n", ++loops);

    memset(image, 0, sizeof(color)*WIDTH*HEIGHT);
    for (int i=0; i<N; i++) {
      dipDrawCircleFill(planets[i].x, planets[i].y, planets[i].r, *planets[i].c);
    }

    char filename[1024];
    sprintf(filename, "images/planets%03d.bmp", loops);
    saveBMP(filename, (unsigned char *) image, WIDTH, HEIGHT, 0);
    */

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
  
  memset(image, 0, sizeof(color)*WIDTH*HEIGHT);
  for (int i=0; i<N; i++) {
    printf("Planet[%d]: x=%f y=%f vx=%f vy=%f m=%f\n", i, planets[i].x, planets[i].y, planets[i].vx, planets[i].vy, planets[i].m);
    dipDrawCircleFill(planets[i].x, planets[i].y, planets[i].r, *planets[i].c);
  }
	
	char filename[1024];
	saveBMP("images/planets000.bmp", (unsigned char *) image, WIDTH, HEIGHT, 0); 

	//timesteps
	for(int t=0; t<TIMESTEPS; t++){		

	  memset(image, 0, sizeof(color)*WIDTH*HEIGHT);

  	planet_moveAll(planets,N);

		//save picture of this TIMESTEP
    for (int i=0; i<N; i++) {
      dipDrawCircleFill(planets[i].x, planets[i].y, planets[i].r, *planets[i].c);
    }
	
		sprintf(filename, "images/planets%03d.bmp", t+1);
		saveBMP(filename, (unsigned char *) image, WIDTH, HEIGHT, 0); 		
	}

  return 0;
}
