#include "planets.h"
#include "intmath.h"
#include "drawcircle.h"

#include <math.h>

int planet_planet_collision(planet p1, planet p2) {
  double radii = p1.r + p2.r;
  int ret = 0;
  if ( fabs(p1.x-p2.x) <= radii ) { // collision x
    ret = 1;
  }
  if ( fabs(p1.y-p2.y) <= radii ) { // collision y
    ret += 2;
  }
  return ret;
}

int planet_edge_collision(planet p) {
  if (p.x < p.r) return 1;
  else if (p.x + p.r > FIELD_MAX_X) return 2;
  else if (p.y < p.r) return 3;
  else if (p.y + p.r > FIELD_MAX_Y) return 4;
  else return 0;
}

int planet_compare(const void *a, const void *b) {
  const planet *p1 = a;
  const planet *p2 = b;
  return p1->x - p2->x;
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
