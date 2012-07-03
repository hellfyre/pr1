#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bitmap.c"

#define WIDTH 500
#define HEIGHT 500

typedef unsigned char byte;
typedef struct {
  byte blue;
  byte green;
  byte red;
} color;

color image[WIDTH*HEIGHT];

void swap (int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void setPixel(int x, int y, color pcolor) {
  image[WIDTH * y + x] = pcolor;
}

void drawLine(int x0, int y0, int x1, int y1, color lcolor) {
  int steep = abs(y1 - y0) > abs(x1 - x0);

  if (steep) {
    swap(&x0, &y0);
    swap(&x1, &y1);
  }
  if (x0 > x1) {
    swap(&x0, &x1);
    swap(&y0, &y1);
  }

  int deltax = x1 - x0;
  int deltay = abs(y1 - y0);
  int error = deltax / 2;
  int ystep;
  int y = y0;

  if (y0 < y1) ystep = 1;
  else ystep = -1;

  for (int x=x0; x<=x1; x++) {
    if (steep) setPixel(y, x, lcolor);
    else setPixel(x, y, lcolor);

    error = error - deltay;
    if ( error < 0) {
      y = y + ystep;
      error = error + deltax;
    }
  }

}

void drawCircle(int x0, int y0, int radius, color ccolor) {
  int f = 1 - radius;
  int ddF_x = 1;
  int ddF_y = -2 * radius;
  int x = 0;
  int y = radius;
 
  setPixel(x0, y0 + radius, ccolor);
  setPixel(x0, y0 - radius, ccolor);
  setPixel(x0 + radius, y0, ccolor);
  setPixel(x0 - radius, y0, ccolor);
 
  while(x < y) {
    // ddF_x == 2 * x + 1;
    // ddF_y == -2 * y;
    // f == x*x + y*y - radius*radius + 2*x - y + 1;
    if(f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;    
    setPixel(x0 + x, y0 + y, ccolor);
    setPixel(x0 - x, y0 + y, ccolor);
    setPixel(x0 + x, y0 - y, ccolor);
    setPixel(x0 - x, y0 - y, ccolor);
    setPixel(x0 + y, y0 + x, ccolor);
    setPixel(x0 - y, y0 + x, ccolor);
    setPixel(x0 + y, y0 - x, ccolor);
    setPixel(x0 - y, y0 - x, ccolor);
  }
}

void drawCircleFill(int x0, int y0, int radius, color ccolor) {
  int f = 1 - radius;
  int ddF_x = 1;
  int ddF_y = -2 * radius;
  int x = 0;
  int y = radius;
 
  drawLine(x0, y0, x0, y0 + radius, ccolor);
  drawLine(x0, y0, x0, y0 - radius, ccolor);
  drawLine(x0, y0, x0 + radius, y0, ccolor);
  drawLine(x0, y0, x0 - radius, y0, ccolor);
 
  while(x < y) {
    // ddF_x == 2 * x + 1;
    // ddF_y == -2 * y;
    // f == x*x + y*y - radius*radius + 2*x - y + 1;
    if(f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;    
    drawLine(x0 - x, y0 + y, x0 + x, y0 + y, ccolor);
    drawLine(x0 - x, y0 - y, x0 + x, y0 - y, ccolor);
    drawLine(x0 - y, y0 + x, x0 + y, y0 + x, ccolor);
    drawLine(x0 - y, y0 - x, x0 + y, y0 - x, ccolor);
  }
}

int main() {
  color someColor;
  someColor.red = 0xab;
  someColor.green = 0xe1;
  someColor.blue = 0x20;

  drawCircleFill(250, 200, 50, someColor);

  /*
  for (int row=0; row<HEIGHT; row++) {
    for (int column=0; column<WIDTH; column++) {
      int elem = WIDTH * row + column;
      if (image[elem] == 0x00) putchar('.');
      else if (image[elem] == 0xff) putchar('0');
      else putchar('?');
    }
    putchar('\n');
  }
  */

  saveBMP("circles.bmp", image, 500, 500, 0);

  return 0;
}
