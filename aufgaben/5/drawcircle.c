#include "drawcircle.h"
#include "intmath.h"

void drawLine(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, color lcolor) {
  int steep = ABS(y1 - y0) > ABS(x1 - x0);

  if (steep) {
    SWAP(x0, y0);
    SWAP(x1, y1);
  }
  if (x0 > x1) {
    SWAP(x0, x1);
    SWAP(y0, y1);
  }

  int deltax = x1 - x0;
  int deltay = ABS(y1 - y0);
  int error = deltax / 2;
  int ystep;
  int y = y0;

  if (y0 < y1) ystep = 1;
  else ystep = -1;

  for (int x=x0; x<=x1; x++) {
    if (steep) SET_PIXEL(y, x, lcolor);
    else SET_PIXEL(x, y, lcolor);

    error = error - deltay;
    if ( error < 0) {
      y = y + ystep;
      error = error + deltax;
    }
  }

}

void drawCircle(unsigned int x0, unsigned int y0, unsigned int radius, color ccolor) {
  int f = 1 - radius;
  int ddF_x = 1;
  int ddF_y = -2 * radius;
  int x = 0;
  int y = radius;
 
  SET_PIXEL(x0, y0 + radius, ccolor);
  SET_PIXEL(x0, y0 - radius, ccolor);
  SET_PIXEL(x0 + radius, y0, ccolor);
  SET_PIXEL(x0 - radius, y0, ccolor);
 
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
    SET_PIXEL(x0 + x, y0 + y, ccolor);
    SET_PIXEL(x0 - x, y0 + y, ccolor);
    SET_PIXEL(x0 + x, y0 - y, ccolor);
    SET_PIXEL(x0 - x, y0 - y, ccolor);
    SET_PIXEL(x0 + y, y0 + x, ccolor);
    SET_PIXEL(x0 - y, y0 + x, ccolor);
    SET_PIXEL(x0 + y, y0 - x, ccolor);
    SET_PIXEL(x0 - y, y0 - x, ccolor);
  }
}

void drawCircleFill(unsigned int x0, unsigned int y0, unsigned int radius, color ccolor) {
  int f = 1 - radius;
  int ddF_x = 1;
  int ddF_y = -2 * radius;
  int x = 0;
  int y = radius;
 
  /*
  drawLine(x0-radius, y0-radius, x0+radius, y0-radius, ccolor);
  drawLine(x0-radius, y0-radius, x0-radius, y0+radius, ccolor);
  drawLine(x0+radius, y0+radius, x0-radius, y0+radius, ccolor);
  drawLine(x0+radius, y0+radius, x0+radius, y0-radius, ccolor);
  */

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

void dipDrawCircleFill(double x0, double  y0, double radius, color ccolor) {
  drawCircleFill((int)x0*WIDTH/FIELD_MAX_X, (int)y0*HEIGHT/FIELD_MAX_Y, (int)radius*WIDTH/FIELD_MAX_X, ccolor);
}
