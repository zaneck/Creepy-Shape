#ifndef CIRCLE2D_H
#define CIRCLE2D_H

char* initPlugin(void);

shape_t createCircle2D(double x, double y, double r);

double valueAt(position2D_t p, shape_t s);

#endif
