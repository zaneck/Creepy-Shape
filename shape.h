#ifndef SHAPE_H
#define SHAPE_H

struct shape_s{
  size_t nbField;
  double* fields;
};

typedef struct shape_s* shape_t;

shape_t newShape(int nbField, ...);
void freeShape(shape_t p);

#endif
