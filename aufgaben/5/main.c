#include "drawcircle.h"
#include "planets.h"
#include "bitmap.c"

int main() {
  planet p1, p2;
  p1.x = 256;
  p1.y = 256;
  p1.r = 100;

  p2.x = 300;
  p2.y = 50;
  p2.r = 20;

  printf("%d\n", collide(p1, p2));
  p2.r = 6;
  printf("%d\n", collide(p1, p2));

  color someColor;
  someColor.red = 0xab;
  someColor.green = 0xe1;
  someColor.blue = 0x20;
  color someOtherColor;
  someOtherColor.red = 0xff;
  someOtherColor.green = 0x10;
  someOtherColor.blue = 0x10;

  dipDrawCircleFill(p1.x, p1.y, p1.r, someColor);
  dipDrawCircleFill(p2.x, p2.y, p2.r, someOtherColor);

  saveBMP("circles.bmp", (unsigned char *) image, WIDTH, HEIGHT, 0);

  return 0;
}
