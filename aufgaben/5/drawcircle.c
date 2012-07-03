#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#define SCREEN_WIDTH 16
#define SCREEN_HEIGHT 10

typedef unsigned char  byte;
typedef unsigned short word;

byte VGA[SCREEN_WIDTH*SCREEN_HEIGHT];
long SIN_ACOS[1024];

/**************************************************************************
 *  circle_fill                                                           *
 *    Draws and fills a circle.                                           *
 **************************************************************************/

void circle_fill(int x,int y, int radius, byte color)
{
  long n=0,invradius=(1/(float)radius)*0x10000L;
  int dx=0,dy=radius-1,i;
  //word dxoffset,dyoffset,offset = (y<<8)+(y<<6)+x;
  word dxoffset, dyoffset;
  word offset = SCREEN_WIDTH * y + x;

  while (dx<=dy)
  {
    //dxoffset = (dx<<8) + (dx<<6);
    //dyoffset = (dy<<8) + (dy<<6);
    dxoffset = SCREEN_WIDTH * x;
    dyoffset = SCREEN_WIDTH * y;
    for(i=dy;i>=dx;i--,dyoffset-=SCREEN_WIDTH)
    {
      VGA[offset+i -dxoffset] = color;  /* octant 0 */
      VGA[offset+dx-dyoffset] = color;  /* octant 1 */
      VGA[offset-dx-dyoffset] = color;  /* octant 2 */
      VGA[offset-i -dxoffset] = color;  /* octant 3 */
      VGA[offset-i +dxoffset] = color;  /* octant 4 */
      VGA[offset-dx+dyoffset] = color;  /* octant 5 */
      VGA[offset+dx+dyoffset] = color;  /* octant 6 */
      VGA[offset+i +dxoffset] = color;  /* octant 7 */
    }
    dx++;
    n+=invradius;
    dy = (int)((radius * SIN_ACOS[(int)(n>>6)]) >> 16);
  }
}

int main() {
  for(int i=0;i<1024;i++) {
    SIN_ACOS[i]=sin(acos((float)i/1024))*0x10000L;
  }

  circle_fill(10, 10, 7, 0x0f);

  for (int row=0; row<SCREEN_HEIGHT; row++) {
    for (int column=0; column<SCREEN_WIDTH; column++) {
      printf("%1x", VGA[row*SCREEN_HEIGHT+column]);
    }
    printf("\n");
  }
}
