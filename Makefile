# usage - all executables placed in ./bin, all .o in ./obj

# make tests		- make all unit tests
# make exercises	- make all chapter exercises
# make programs		- make any other programs made during process

# make library		- make libgeolib.a from .o files

# make clean		- self explanatory
# make cleanlib
# make cleanobj
# make cleanbin

# search in these folders for any .c files
vpath %.c src/ src/geometry src/graphics src/test src/exercises src/programs src/util

# Compiler
CC = gcc
CCFLAGS = -g -Wall

# Folders
# library files
SOURCES = tuple.c gmaths.c color.c mem.c log.c canvas.c file.c matrix.c ray.c sphere.c
OBJECTS = $(patsubst %.c, obj/%.o, $(SOURCES))
LIBRARY = lib/libraytracer.a

INCLUDE = -I./inc/
MYLIBS = -lraytracer
CLIBS = -lm

TEST_SOURCES = $(notdir $(wildcard src/test/*.c))
TESTS := $(addprefix bin/, $(notdir $(TEST_SOURCES:.c=)))

EXERCISE_SOURCES = $(notdir $(wildcard src/exercises/*.c))
EXERCISES := $(addprefix bin/, $(notdir $(EXERCISE_SOURCES:.c=)))

PROG_SOURCES = $(notdir $(wildcard src/programs/*.c))
PROGRAMS := $(addprefix bin/, $(notdir $(PROG_SOURCES:.c=)))

# for user specified inputs
OUTPUT = $(addprefix bin/, $(notdir $(INPUT:.c=)))

# rules
$(shell mkdir -p bin)

# create the obj folder if needed
$(OBJECTS): | obj

obj:
	@mkdir -p $@
	
obj/%.o: %.c
	@echo $<
	@$(CC) $(CCFLAGS) $(INCLUDE) -c $< -o $@ $(CLIBS)
	
library: $(OBJECTS)
	ar rcs $(LIBRARY) $(OBJECTS)

tests: library $(TESTS)

exercises: library $(EXERCISES)

programs: library $(PROGRAMS)

bin/%: %.c
	$(CC) $(CCFLAGS) $(INCLUDE) -L./lib $< -o $@ $(MYLIBS) $(CLIBS)
	
input: $(INPUT) library
	$(CC) $(CCFLAGS) $(INCLUDE) -L./lib $< -o $(OUTPUT) $(MYLIBS) $(CLIBS)

# cleanup

.PHONY: clean cleanlib cleanall cleanbin

clean: cleanlib cleanobj
	
cleanobj:
	rm -rf obj/*
	
cleanlib:
	rm -rf lib/*
	
cleanbin:
	rm -rf bin/*
	
cleanall: cleanbin cleanlib cleanobj
	
testsuite:
	@echo Objects: $(OBJECTS)
	@echo Library: $(LIBRARY)
	@echo Testsources: $(TEST_SOURCES)
	@echo Test progs: $(TESTS)
	@echo Ex sources: $(EXERCISE_SOURCES)
	@echo Ex progs: $(EXERCISES)
	@echo Program Sources: $(PROG_SOURCES)
	@echo Programs: $(PROGRAMS)
