#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <dlfcn.h>
#include <assert.h>

#include <search.h>

#include "position2D.h"
#include "shape.h"

/* struct element { */
/*   struct element *forward; */
/*   struct element *backward; */
/*   char *name; */
/* }; */

/* static struct element * */
/* new_element(void) */
/* { */
/*   struct element *e; */

/*   e = malloc(sizeof(struct element)); */
/*   if (e == NULL) { */
/*     fprintf(stderr, "malloc() failed\n"); */
/*     exit(EXIT_FAILURE); */
/*   } */

/*   return e; */
/* } */



int
main(void){
  /* /\* PLUGIN *\/ */
  /* void (*fun)(void); */

  /* void* libhandle = dlopen("./plugins/hello.so", RTLD_NOW); */

  /* *(void **) (&fun) = dlsym(libhandle, "printMe"); */

  /* (*fun)(); */
  
  /* dlclose(libhandle); */

  char *test;
  char *error;  
  char* (*funInit)(void);
  shape_t (*createCircle)(int, ...);
  double (*valueAtCircle)(position2D_t , shape_t );
  void* libhandle;
  
  libhandle = dlopen("plugins/shapes/circle2D.so", RTLD_NOW);

  if (!libhandle) {
    fprintf(stderr, "%s\n", dlerror());
    exit(EXIT_FAILURE);
  }
  
  printf("load\n");
  
  *(void **) (&funInit) = dlsym(libhandle, "initPlugin");
  error = dlerror();
  if (error != NULL) {
    fprintf(stderr, "%s\n", error);
    exit(EXIT_FAILURE);
  }

  test = (*funInit)();
  
  *(void **) (&createCircle) = dlsym(libhandle, "createShape");  
  error = dlerror();
  if (error != NULL) {
    fprintf(stderr, "%s\n", error);
    exit(EXIT_FAILURE);
  }

  *(void **) (&valueAtCircle) = dlsym(libhandle, "valueAt");
  error = dlerror();
  if (error != NULL) {
    fprintf(stderr, "%s\n", error);
    exit(EXIT_FAILURE);
  }
  

  printf("%s\n",test);


  shape_t circle;
  circle = (*createCircle)(3, 1.0, 1.0, 1.0);

  double value;
  struct position2D_s p;
  p.x = 1.0;
  p.y = 0.0;

  value = (*valueAtCircle)(&p, circle);
  printf("%f\n", value);
  dlclose(libhandle);

  /*not secure*/
  free(test);
  
  /* /\* HASHMAP *\/ */
  /* struct hsearch_data *hashTable; */

  /* hashTable = (struct hsearch_data *) calloc((size_t)1, sizeof(struct hsearch_data));; */
  
  /* int status; */
  /* ENTRY e; */
  /* ENTRY *returnValue; */

  /* e.key = "Tango"; */
  /* e.data = (void*) 1; */
  
  /* status = hcreate_r((size_t) 30, hashTable); */
  /* printf("status create %d\n",status); */
  
  /* status = hsearch_r(e, ENTER, &returnValue, hashTable); */
  /* printf("status enter %d\n",status); */

  /* status = hsearch_r(e, FIND, &returnValue, hashTable); */
  /* printf("status enter OK %d\n",status); */

  /* e.key = "Charly"; */
  /* status = hsearch_r(e, FIND, &returnValue, hashTable); */
  /* printf("status enter KO %d\n",status); */
  
  /* free(returnValue); */
  /* hdestroy_r(hashTable); */

  /* free(hashTable); */
  
  /* /\* LIST *\/ */
  
  /* struct element *first, *elem, *prev; */


  /* /\* Create first element and place it in the linked list *\/ */

  /* elem = new_element(); */
  /* first = elem; */

  /* elem->name = "one"; */

  /* insque(elem, NULL); */
  /* printf("\ninsert one\n"); */
  
  /* prev = elem; */

  /* elem = new_element(); */
  /* printf("insert three after one\n"); */
  /* elem->name = "Three"; */
  /* insque(elem, prev); */

  /* elem = new_element(); */
  /* printf("insert two after one\n"); */
  /* elem->name = "Two"; */
  /* insque(elem, prev); */
  
  /* /\* Traverse the list from the start, printing element names *\/ */

  /* printf("Traversing completed list:\n"); */
  /* elem = first; */
  /* do { */
  /*   printf("    %s\n", elem->name); */
  /*   elem = elem->forward; */
  /* } while (elem != NULL && elem != first); */

  /* printf("remove one\n"); */

  /* elem = first; */
  /* first = first->forward; */

  /* remque(elem); */
  /* free(elem); */

  /* printf("Traversing completed list:\n"); */
  /* elem = first; */
  /* do { */
  /*   printf("    %s\n", elem->name); */
  /*   elem = elem->forward; */
  /* } while (elem != NULL && elem != first); */

  /* printf("free list elem\n"); */
  /* elem = first; */
  /* do { */
  /*   first = elem; */
  /*   elem = first->forward; */
  /*   free(first); */
  /* } while (elem != NULL && elem != first); */
  
  return 0;
}
