#ifndef SHAPE_H
#define SHAPE_H

#include "position.h"

struct shape_s{
  size_t nbField;
  double* fields;
  double (*valueAt)(position_t, struct shape_s*);
  char* id;
};

typedef struct shape_s* shape_t;

shape_t newShape(char* id, int nbField, ...);
void freeShape(shape_t p);

#endif
