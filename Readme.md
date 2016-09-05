# Creepy-Shape

STATUS
------

WIP on pluging system

##Plugin system
###With C and DSO (Dynamic Shared Objects)

####Core

Load plugin and print plugin message (printMe)


### INCANTATUM
for hello plugin

gcc -c plugin/hello.c -o plugin/hello.o -pedantic -g -Wall -std=c99 -fpic -I.
gcc -o plugin/hello.so plugin/hello.o -shared