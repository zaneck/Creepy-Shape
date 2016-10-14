#include <stdlib.h>
#include <stdio.h>
#include <search.h>
#include <unistd.h>
#include <dlfcn.h>
#include "pluginManager.h"


pluginManager_t
allocPluginManager(void){
  int status;
  pluginManager_t res;
  res = (pluginManager_t)malloc(sizeof(struct pluginManager_s));

  res->shapes = (struct hsearch_data *) calloc((size_t)1, sizeof(struct hsearch_data));;
  status = hcreate_r((size_t) 30, res->shapes);
  if (status == 0) {
    fprintf(stderr, "error create shapes hsearch\n");
    exit(EXIT_FAILURE);
  }

  res->listOfShape = NULL;
  
  res->operations = (struct hsearch_data *) calloc((size_t)1, sizeof(struct hsearch_data));;
  status = hcreate_r((size_t) 30, res->operations);
  if (status == 0) {
    fprintf(stderr, "error create operations hsearch\n");
    exit(EXIT_FAILURE);
  }
  
  return res;
}

void
freePluginManager(pluginManager_t pm){
  struct elementShape_s *elt, *tmp;

  hdestroy_r(pm->shapes);
  hdestroy_r(pm->operations);
  free(pm->shapes);
  free(pm->operations);

  elt = pm->listOfShape;

  do{
    tmp = elt;
    elt = tmp->forward;
    remque(tmp);
    dlclose(tmp->libhandle);
    free(tmp->plug->id);
    free(tmp->plug);
    free(tmp);
  }while(elt != NULL);
  
  free(pm);

  /* free plug ref and close libhandle */

}

void
addShapePlugin(char* plugin, pluginManager_t pm){
  void* libhandle; /*open the .so*/
  char* error; /*dlopen dlsym error*/
  char* id; /*name of the plug*/
  pluginShape_t plug; /*plug create*/
  struct elementShape_s *head; /*List saving*/
  /* int status; /\*error hsearch*\/ */
  ENTRY e, *returnValue; /*enter the hsearch*/
  
  libhandle = dlopen(plugin, RTLD_NOW);

  if (!libhandle) {
    fprintf(stderr, "%s\n", dlerror());
    exit(EXIT_FAILURE);
  }

  char* (*funInit)(void);
  *(void **) (&funInit) = dlsym(libhandle, "initPlugin");
  error = dlerror();
  if (error != NULL) {
    fprintf(stderr, "%s\n", error);
    exit(EXIT_FAILURE);
  }

  id = (*funInit)();

  printf("addPlugin %s\n", id);
  
  plug = (pluginShape_t) malloc(sizeof(struct pluginShape_s));
  plug->id = id;
  
  *(void**) &plug->createShape = dlsym(libhandle, "createShape"); 
  error = dlerror();
  if (error != NULL) {
    fprintf(stderr, "%s\n", error);
    exit(EXIT_FAILURE);
  }
  *(void**) &plug->valueAt = dlsym(libhandle, "valueAt");

  error = dlerror();
  if (error != NULL) {
    fprintf(stderr, "%s\n", error);
    exit(EXIT_FAILURE);
  }

  /*libhandle open, dlsym done, plugin_t create*/
  /*save to the list*/
  head = (struct elementShape_s *) malloc(sizeof(struct elementShape_s));
  head->libhandle = libhandle;
  head->plug = plug;
  if(pm->listOfShape == NULL){
    insque(head,NULL);
    pm->listOfShape = head; 
  }
  else{
    insque(head, pm->listOfShape);
  }

  /*save to hsearch*/
  e.key = id;
  e.data = (void*) plug;
  /* status =  */hsearch_r(e, ENTER, &returnValue, pm->shapes);
  /* printf("status enter %d\n",status); */
}

	   
