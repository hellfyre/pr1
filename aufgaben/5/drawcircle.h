#ifndef __DRAWCIRCLE_H__
#define __DRAWCIRCLE_H__

#define WIDTH 500
#define HEIGHT 500

typedef unsigned char byte;

typedef struct {
  byte blue;
  byte green;
  byte red;
} color;

#define SET_PIXEL(x, y, pcolor) image[WIDTH * y + x] = pcolor

void drawLine(int x0, int y0, int x1, int y1, color lcolor);
void drawCircle(int x0, int y0, int radius, color ccolor);
void drawCircleFill(int x0, int y0, int radius, color ccolor);

#endif /* __DRAWCIRCLE_H__ */
