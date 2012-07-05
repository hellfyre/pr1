#ifndef __DRAWCIRCLE_H__
#define __DRAWCIRCLE_H__

#define WIDTH 1024
#define HEIGHT WIDTH
#define FIELD_MAX_X 512
#define FIELD_MAX_Y FIELD_MAX_X
#define RADIUS_MAX FIELD_MAX_X/64

typedef unsigned char byte;

typedef struct {
  byte blue;
  byte green;
  byte red;
} color;

#define SET_PIXEL(x, y, pcolor) image[WIDTH * y + x] = pcolor

void drawLine(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, color lcolor);
void drawCircle(unsigned int x0, unsigned int y0, unsigned int radius, color ccolor);
void drawCircleFill(unsigned int x0, unsigned int y0, unsigned int radius, color ccolor);
void dipDrawCircleFill(double x0, double  y0, double radius, color ccolor);

color image[WIDTH*HEIGHT];

#endif /* __DRAWCIRCLE_H__ */
