#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <stdarg.h>

#include "shape.h"

shape_t
newShape(int nbField, ...){
  shape_t s;
  va_list fields;
  double f;
  
  s = (shape_t) malloc(sizeof(struct shape_s));
  s->nbField = nbField;

  s->fields = (double*)calloc((size_t)nbField, sizeof(double)); 

  va_start(fields, nbField);
  for(int i=0; i<nbField; i++){
    f = va_arg(fields, double);
    s->fields[i] = f;
  }
  va_end(fields);
  return s;
}

void
freeShape(shape_t p){
  free(p->fields);
  free(p);

}
