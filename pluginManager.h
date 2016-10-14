#ifndef  PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include "shape.h"
#include "position.h"

struct pluginShape_s{
  shape_t (*createShape)(int, ...);
  double (*valueAt)(position_t , shape_t );
  char* id;
};

typedef struct pluginShape_s* pluginShape_t;

struct elementShape_s {
  struct elementShape_s *forward;
  struct elementShape_s *backward;
  pluginShape_t plug;
  void* libhandle;
};

struct pluginManager_s{
  struct hsearch_data *shapes;
  struct elementShape_s *listOfShape;
  
  struct hsearch_data *operations;

};

typedef struct pluginManager_s* pluginManager_t;

/* Alloc and free regular */
pluginManager_t allocPluginManager(void);
void freePluginManager(pluginManager_t);

/* Add plugin to the manager, with file path*/
void addShapePlugin(char*, pluginManager_t);
/* int loadFolder_pluginManager(const char*); */

/* /\* Return the list of plugin available *\/ */
/* char* listObject_pluginManager(pluginManager_t) */

#endif
