#include "drawcircle.h"
#include "planets.h"
#include "bitmap.c"

int main() {
  planet p1, p2;
  p1.x = 10;
  p1.y = 10;
  p1.r = 5;

  p2.x = 20;
  p2.y = 20;
  p2.r = 3;

  printf("%d\n", collide(p1, p2));
  p2.r = 6;
  printf("%d\n", collide(p1, p2));

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
