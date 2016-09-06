# Makefile type
# Edit by Valentin Owczarek, 30 juillet 2015
##############################################################################

CC	= gcc
CFLAGS  = -pedantic -Wall -Wextra -Wstrict-prototypes
CFLAGS += -Wtraditional-conversion -Wpointer-arith -Wcast-qual
CFLAGS += -Wmissing-prototypes -std=c99
CFLAGS += -g #DEBUG
CFLAGS += -Werror -D_GNU_SOURCE #No human option
LDFLAGS = -ldl 

CFLIBFLAGS = -fpic -I.
LDLIBFLAGS = -shared

###------------------------------
### targets 
###------------------------------------------------------------
BINARIES= main

PLUGINS =  hello

BIN_OBJ = $(addsuffix .o, $(BINARIES))

PLU_PATH = $(addprefix plugins/, $(PLUGINS))
PLU_OBJ = $(addsuffix .o, $(PLU_PATH))
PLU_LIB = $(addsuffix .so, $(PLU_PATH))

TRASHFILES=*~

all: $(BINARIES) $(PLU_LIB)


###------------------------------
### Main rules 
###------------------------------------------------------------
main: main.o
	$(CC) $(LDFLAGS) -o $@ $^ 

plugins/hello.o: plugins/hello.c
	$(CC) -c $^ -o $@ $(CFLAGS) $(CFLIBFLAGS)

plugins/hello.so: plugins/hello.o
	$(CC) $(LDLIBFLAGS) -o $@ $^


###------------------------------
### Misc.
###------------------------------------------------------------
.PHONY: clean realclean depend
clean:
	$(RM) $(BIN_OBJ) $(PLU_OBJ)

realclean: clean 
	$(RM) $(BINARIES) $(PLU_LIB)

depend: 
	$(CC) $(CFLAGS) -MM *.c
