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

###-----------------------------------------------
### TARGETS -------------------------------------- 
###-----------------------------------------------
BINARIES= main

TOOLS= position2D shape

PLUGINS_SHAPES =  circle2D circle3D

###-----------------------------------------------
### RULES TO MAKE THE WORLD ----------------------
###-----------------------------------------------
BIN_OBJ = $(addsuffix .o, $(BINARIES))

TOOLS_OBJ = $(addsuffix .o, $(TOOLS))

PLU_SHAPES_PATH = $(addprefix plugins/shapes/, $(PLUGINS_SHAPES))
PLU_SHAPES_OBJ = $(addsuffix .o, $(PLU_SHAPES_PATH))
PLU_SHAPES_LIB = $(addsuffix .so, $(PLU_SHAPES_PATH))

TRASH = *~ */*~ */*/*~

all: $(BINARIES) $(PLU_SHAPES_LIB) 

###-----------------------------------------------
### RULES ---------------------------------------- 
###-----------------------------------------------
main: main.o 
	$(CC) $(LDFLAGS) -o $@ $^ 

./%.o: ./%.c 
	$(CC) $(CFLAGS) -fPIC -c $^ -o $@

plugins/shapes/%.o: plugins/shapes/%.c  
	$(CC) $(CFLAGS) $(CFLIBFLAGS) -c $^ -o $@

plugins/shapes/%.so: plugins/shapes/%.o $(TOOLS_OBJ) 
	$(CC) $(CFLIBFLAGS) $(LDLIBFLAGS) -o $@ $^


###------------------------------
### Misc.
###------------------------------------------------------------
.PHONY: clean realclean depend
clean:
	$(RM) $(BIN_OBJ) $(PLU_SHAPES_OBJ) $(TOOLS_OBJ) $(TRASH)

realclean: clean 
	$(RM) $(BINARIES) $(PLU_LIB) $(PLU_SHAPES_LIB)

depend: 
	$(CC) $(CFLAGS) -MM *.c
