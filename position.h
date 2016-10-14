#ifndef POSITION_H
#define POSITION_H

struct position_s{
  double x;
  double y;
  double z;
};

typedef struct position_s* position_t;

position_t newPosition(double x, double y, double z);
void freePosition(position_t p);

void setPosition(position_t p, double x, double y, double z);

double euclideanDist(position_t p1, position_t p2);

#endif
