#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#define WIDTH 157
#define HEIGHT 64

typedef unsigned char byte;

byte image[WIDTH*HEIGHT];

void swap (int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void setPixel(int x, int y) {
  image[WIDTH * y + x] = 0xff;
}

void drawLine(int x0, int y0, int x1, int y1) {
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
    if (steep) setPixel(y,x);
    else setPixel(x,y);

    error = error - deltay;
    if ( error < 0) {
      y = y + ystep;
      error = error + deltax;
    }
  }

}

void drawCircle(int x0, int y0, int radius) {
  int f = 1 - radius;
  int ddF_x = 1;
  int ddF_y = -2 * radius;
  int x = 0;
  int y = radius;
 
  setPixel(x0, y0 + radius);
  setPixel(x0, y0 - radius);
  setPixel(x0 + radius, y0);
  setPixel(x0 - radius, y0);
 
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
    setPixel(x0 + x, y0 + y);
    setPixel(x0 - x, y0 + y);
    setPixel(x0 + x, y0 - y);
    setPixel(x0 - x, y0 - y);
    setPixel(x0 + y, y0 + x);
    setPixel(x0 - y, y0 + x);
    setPixel(x0 + y, y0 - x);
    setPixel(x0 - y, y0 - x);
  }
}

void drawCircleFill(int x0, int y0, int radius) {
  int f = 1 - radius;
  int ddF_x = 1;
  int ddF_y = -2 * radius;
  int x = 0;
  int y = radius;
 
  drawLine(x0, y0, x0, y0 + radius);
  drawLine(x0, y0, x0, y0 - radius);
  drawLine(x0, y0, x0 + radius, y0);
  drawLine(x0, y0, x0 - radius, y0);
 
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
    drawLine(x0 - x, y0 + y, x0 + x, y0 + y);
    drawLine(x0 - x, y0 - y, x0 + x, y0 - y);
    drawLine(x0 - y, y0 + x, x0 + y, y0 + x);
    drawLine(x0 - y, y0 - x, x0 + y, y0 - x);
  }
}

int main() {
  drawCircleFill(30, 25, 10);

  for (int row=0; row<HEIGHT; row++) {
    for (int column=0; column<WIDTH; column++) {
      int elem = WIDTH * row + column;
      if (image[elem] == 0x00) putchar('.');
      else if (image[elem] == 0xff) putchar('0');
      else putchar('?');
    }
    putchar('\n');
  }
}
