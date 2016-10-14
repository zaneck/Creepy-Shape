#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "position.h"

position_t
newPosition(double x, double y, double z){
  position_t p;
  p = (position_t) malloc(sizeof(struct position_s));

  p->x = x;
  p->y = y;
  p->z = z;
  
  return p;
}

void freePosition(position_t p){
  free(p);
}

void setPosition(position_t p, double x, double y, double z){
  p->x = x;
  p->y = y;
  p->z = z;
}

double euclideanDist(position_t p1, position_t p2){
  double x, y, z;
  x= p1->x - p2->x;
  y= p1->y - p2->y;
  z= p1->z - p2->z;
  
  return sqrt( pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));
}
