# Makefile type
# Edit by Valentin Owczarek, 30 juillet 2015
##############################################################################

CC	= gcc
CFLAGS  = -pedantic -Wall -Wextra -Wstrict-prototypes
CFLAGS += -Wtraditional-conversion -Wpointer-arith -Wcast-qual
CFLAGS += -Wmissing-prototypes -std=c99
CFLAGS += -g #DEBUG
CFLAGS += -Werror -D_GNU_SOURCE #No human option
LDFLAGS = -ldl -g -lm 

CFLIBFLAGS = -fPIC -I.
LDLIBFLAGS = -shared

###------------------------------
### targets 
###------------------------------------------------------------
BINARIES= main

PLUGINS_SHAPES =  circle2d circle3d

BIN_OBJ = $(addsuffix .o, $(BINARIES))

PLU_SHAPES_PATH = $(addprefix plugins/shapes/, $(PLUGINS_SHAPES))
PLU_SHAPES_OBJ = $(addsuffix .o, $(PLU_SHAPES_PATH))
PLU_SHAPES_LIB = $(addsuffix .so, $(PLU_SHAPES_PATH))


TRASHFILES=*~

all: $(BINARIES) $(PLU_SHAPES_LIB)


###------------------------------
### Main rules 
###------------------------------------------------------------
main: main.o
	$(CC) $(LDFLAGS) -o $@ $^ 

plugins/shapes/%.o: plugins/shapes/%.c
	$(CC) $(CFLAGS) $(CFLIBFLAGS) -c $^ -o $@

plugins/shapes/%.so: plugins/shapes/%.o
	$(CC) $(CFLIBFLAGS) $(LDLIBFLAGS) -o $@ $^


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
