#include "planets.h"
#include "intmath.h"

#include <math.h>

int collide(planet p1, planet p2) {
  int radii = p1.r + p2.r;
  return (  ( ABS(p1.x-p2.x) <= radii ) &&
            ( ABS(p1.y-p2.y) <= radii ) );
}
