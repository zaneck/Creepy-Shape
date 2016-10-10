#ifndef POSITION2D_H
#define POSITION2D_H

struct position2D_s{
  double x;
  double y;
};

typedef struct position2D_s* position2D_t;

position2D_t newPosition2D(double x, double y);
void freePosition2D(position2D_t p);

void setPosition2D(position2D_t p, double x, double y);

double euclideanDist2D(position2D_t p1, position2D_t p2);

#endif
