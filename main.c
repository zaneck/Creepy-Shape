#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <assert.h>

#include <search.h>

#include "position.h"
#include "shape.h"
#include "pluginManager.h"


int
main(void){
  /* double test; */
  pluginManager_t pm;

  pm = allocPluginManager();
  addShapePlugin("plugins/shapes/circle2D.so", pm);
  
  ENTRY e, *returnValue; /*hsearch*/
  int status;
  pluginShape_t sp;
  shape_t s;
  
  e.key="c2d";

  status = hsearch_r(e, FIND, &returnValue, pm->shapes);

  printf("%d\n", status);

  sp = (pluginShape_t) returnValue->data;
  s = sp->createShape(4, 0, 0, 0, 1);
  printf("nbField %zu, name %s\n", s->nbField, s->id);

  freeShape(s);
  freePluginManager(pm);
  
  return 0;
}
