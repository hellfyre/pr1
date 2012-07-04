#include "planets.h"
#include "intmath.h"

#include <math.h>

int collide(planet p1, planet p2) {
  double radii = p1.r + p2.r;
  return (  ( fabs(p1.x-p2.x) <= radii ) &&
            ( fabs(p1.y-p2.y) <= radii ) );
}

planet com(planet planets[], int size) {
  planet center;
  center.x = 0;
  center.y = 0;
  center.m = 0;
  center.r = 0;
  center.vx = 0;
  center.vy = 0;
  for (int i=0; i<size; i++) {
    center.m += planets[i].m;
    center.x += planets[i].x * planets[i].m;
    center.y += planets[i].y * planets[i].m;
  }
  center.x /= center.m;
  center.y /= center.m;

  return center;
}
