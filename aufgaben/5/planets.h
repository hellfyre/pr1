#ifndef __PLANETS_H__
#define __PLANETS_H__

typedef struct {
  double x;  // x-pos
  double y;  // y-pos
  double vx; // x-velocity
  double vy; // y-velocity
  double m;  // mass
  double r;  // radius
} planet;

int collide(planet p1, planet p2);
planet com(planet planets[], int size);

#endif /* __PLANETS_H__ */
