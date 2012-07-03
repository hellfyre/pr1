#include "drawcircle.c"
#include "bitmap.c"

int main() {
  color someColor;
  someColor.red = 0xab;
  someColor.green = 0xe1;
  someColor.blue = 0x20;

  drawCircleFill(250, 200, 50, someColor);

  saveBMP("circles.bmp", (unsigned char *) image, WIDTH, HEIGHT, 0);

  return 0;
}

