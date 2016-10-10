#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "position2D.h"

position2D_t
newPosition2D(double x, double y){
  position2D_t p;
  p = (position2D_t) malloc(sizeof(struct position2D_s));

  p->x = x;
  p->y = y;
  
  return p;
}

void freePosition2D(position2D_t p){
  free(p);
}

void setPosition2D(position2D_t p, double x, double y){
  p->x = x;
  p->y = y;
}

double euclideanDist2D(position2D_t p1, position2D_t p2){
  double x, y;
  x= p1->x - p2->x;
  y= p1->y - p2->y;
  return sqrt( pow(x, 2.0) + pow(y, 2.0) );
}
