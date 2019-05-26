# search in these folders for any .c files
vpath %.c src/ src/geometry

# Compiler
CC = gcc
CCFLAGS = -g -Wall

# Folders
# library files
SOURCES = tuple.c gmaths.c
OBJECTS = $(patsubst %.c, obj/%.o, $(SOURCES))

INCLUDE = -I./inc/
CLIBS = -lm

TESTSOURCES = $(wildcard src/test/*.c)
TESTS := $(addprefix bin/, $(notdir $(TESTSOURCES:.c=)))


# rules

# create the obj folder if needed
$(OBJECTS): | obj

obj:
	@mkdir -p $@
	
obj/%.o: %.c
	@echo $<
	@$(CC) $(CCFLAGS) $(INCLUDE) -c $< -o $@ $(CLIBS)
	
library: $(OBJECTS)
	ar rcs lib/libgeolib.a $(OBJECTS)

test: library $(TESTS)

%: %.c
	$(CC) $(CCFLAGS) $(INCLUDE) -L./lib $< -o $@ -lgeolib -lm
	
testsuite:
	@echo $(TESTSOURCES)
	@echo $(TESTS)
