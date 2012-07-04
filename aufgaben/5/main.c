#include "drawcircle.h"
#include "planets.h"
#include "bitmap.c"

int main() {
  planet p1, p2, p3;
  p1.x = 10;
  p1.y = 10;
  p1.r = 5;

  p2.x = 20;
  p2.y = 20;
  p2.r = 3;

  printf("%d\n", collide(p1, p2));
  p2.r = 6;
  printf("%d\n", collide(p1, p2));

  p1.x = 2;
  p1.y = 1;
  p1.m = 5;
  p2.x = 2;
  p2.y = 3;
  p2.m = 7;
  p3.x = 4;
  p3.y = 2;
  p3.m = 20;
  planet planets[3];
  planets[0] = p1;
  planets[1] = p2;
  planets[2] = p3;

  planet sum = com(planets, 3);

  printf("sum x=%f y=%f m=%f\n", sum.x, sum.y, sum.m);

  /*
  color someColor;
  someColor.red = 0xab;
  someColor.green = 0xe1;
  someColor.blue = 0x20;

  drawCircleFill(250, 200, 50, someColor);

  saveBMP("circles.bmp", (unsigned char *) image, WIDTH, HEIGHT, 0);
  */

  return 0;
}
