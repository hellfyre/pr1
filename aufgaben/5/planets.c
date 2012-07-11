#include "planets.h"
#include "intmath.h"
#include "drawcircle.h"

#include <math.h>

/* take one planet & calc new velocity based on mass and position (gravity) of all other planets, then move him in that direction */
void planet_moveAll(planet planets[], int size){	
  /*
	double distance,directionx,directiony,accelerationAmount;	

	for (int j=0; j<size; j++) {
	  	for (int k=0; k<size && j!=k; k++) {
				//calc new veclocity
				distance = sqrt((planets[j].x - planets[k].x)*(planets[j].x - planets[k].x) + (planets[j].y - planets[k].y)*(planets[j].y - planets[k].y));
				directionx = planets[k].x - planets[j].x;
				directiony = planets[k].y - planets[j].y;
				accelerationAmount = planets[k].m/(distance*distance);

				planets[j].vx += accelerationAmount*directionx;		
				planets[j].vy += accelerationAmount*directiony;		

				//check collision
				if(planet_planet_collision(planets[j],planets[k]) > 0){
					//printf("collision of planet %d with planet %d\n",j,k);
					bewegungsrichtungUmkehren(planets[j]);
					bewegungsrichtungUmkehren(planets[k]);

				}
				//printf("%d with %d: distance=%f	vx:%f	vy:%f\n",j,k,distance,planets[j].vx,planets[j].vy);
			}
			//move planet
			planets[j].x = planets[j].x + planets[j].vx;
			planets[j].y = planets[j].y + planets[j].vy;
		
			//draw planet
   		dipDrawCircleFill(planets[j].x, planets[j].y, planets[j].r, *planets[j].c);
	  }
	*/
}

void bewegungsrichtungUmkehren(planet *p){
		p->vx *= -1;
		p->vy *= -1;
}

int planet_planet_collision(planet p1, planet p2) {
  double radii = p1.r + p2.r;
  return ( fabs(p1.x-p2.x) <= radii && fabs(p1.y-p2.y) <= radii );
}

int planet_edge_collision(planet p) {
  if (p.x < p.r) return 1;
  else if (p.x + p.r > FIELD_MAX_X) return 2;
  else if (p.y < p.r) return 3;
  else if (p.y + p.r > FIELD_MAX_Y) return 4;
  else return 0;
}

int planet_compare(const void *a, const void *b) {
  const planet *p1 = a;
  const planet *p2 = b;
  return p1->x - p2->x;
}

planet com(planet planets[], int size) {
  planet center;
  center.x = 0;
  center.y = 0;
  center.m = 0;
  center.r = 0;
  center.vx = 0;
  center.vy = 0;
  for (int i=0; i<size; i++) {
    center.m += planets[i].m;
    center.x += planets[i].x * planets[i].m;
    center.y += planets[i].y * planets[i].m;
  }
  center.x /= center.m;
  center.y /= center.m;

  return center;
}
