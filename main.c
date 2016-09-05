#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int
main(void){
  void (*fun)(void);
  
  void* libhandle = dlopen("./plugins/hello.so", RTLD_NOW);

  *(void **) (&fun) = dlsym(libhandle, "printMe");

  (*fun)();
  
  dlclose(libhandle);
  
  return 0;
}
