#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#include "position.h"
#include "shape.h"
#include "circle2D.h"

char*
initPlugin(void){
  char* l;
  l = (char*) calloc((size_t)5, sizeof(char));  

  strcpy(l, "c2d");
  printf("init ok\n");
  return l;
}


shape_t
createShape(int nbfield, ...){
  if (nbfield != 3){
    printf("The circle shape need 3 fields, x, y, radius\n");
    exit(EXIT_FAILURE);
  }
  shape_t s;
  double x, y, r;

  va_list fields;
  va_start(fields, nbfield);
  x = va_arg(fields, double);
  y = va_arg(fields, double);
  r = va_arg(fields, double);
  
  s = newShape(3, x, y, r);
  return s;
}

double
valueAt(position_t p, shape_t s){
  struct position_s c;
  c.x = s->fields[0];
  c.y = s->fields[1];
  
  return euclideanDist(p, &c) - s->fields[2];
}
