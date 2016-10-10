#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "position2D.h"
#include "shape.h"
#include "circle2D.h"

char*
initPlugin(void){
  char* l;
  l = (char*) calloc((size_t)20, sizeof(char));  

  strcpy(l, "c2d");
  printf("init ok\n");
  return l;
}


shape_t
createCircle2D(double x, double y, double r){
  shape_t s;
  s = newShape(3, x, y, r);
  return s;
}

double
valueAt(position2D_t p, shape_t s){
  struct position2D_s c;
  c.x = s->fields[0];
  c.y = s->fields[1];
  
  return euclideanDist2D(p, &c) - s->fields[2];
}