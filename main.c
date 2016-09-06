#include <stdio.h>
#include <stdlib.h>

#include <dlfcn.h>

#include <search.h>

int
main(void){
  void (*fun)(void);
  
  void* libhandle = dlopen("./plugins/hello.so", RTLD_NOW);

  *(void **) (&fun) = dlsym(libhandle, "printMe");

  (*fun)();
  
  dlclose(libhandle);

  struct hsearch_data *hashTable;

  hashTable = (struct hsearch_data *) calloc((size_t)1, sizeof(struct hsearch_data));;
  
  int status;
  ENTRY e;
  ENTRY *returnValue;

  returnValue = (ENTRY*) malloc(sizeof(ENTRY));

  e.key = "Tango";
  e.data = (void*) 1;
  
  status = hcreate_r((size_t) 30, hashTable);
  printf("status create %d\n",status);
  
  status = hsearch_r(e, ENTER, &returnValue, hashTable);
  printf("status enter %d\n",status);

  status = hsearch_r(e, FIND, &returnValue, hashTable);
  printf("status enter OK %d\n",status);

  e.key = "Charly";
  status = hsearch_r(e, FIND, &returnValue, hashTable);
  printf("status enter KO %d\n",status);
  
  
  hdestroy_r(hashTable);

  free(hashTable);
  
  return 0;
}
