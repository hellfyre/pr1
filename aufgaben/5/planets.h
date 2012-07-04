#ifndef __PLANETS_H__
#define __PLANETS_H__

typedef struct {
  int x;  // x-pos
  int y;  // y-pos
  int vx; // x-velocity
  int vy; // y-velocity
  int m;  // mass
  int r;  // radius
} planet;

int collide(planet p1, planet p2);

#endif /* __PLANETS_H__ */
