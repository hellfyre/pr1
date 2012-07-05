#ifndef __PLANETS_H__
#define __PLANETS_H__

#include "drawcircle.h"

typedef struct {
  double x;  // x-pos
  double y;  // y-pos
  double vx; // x-velocity
  double vy; // y-velocity
  double m;  // mass
  double r;  // radius
  color *c;
} planet;

int planet_planet_collision(planet p1, planet p2);
int planet_edge_collision(planet p);
int planet_compare(const void *a, const void *b);
planet com(planet planets[], int size);

#endif /* __PLANETS_H__ */
