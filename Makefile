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
vpath %.c src/ src/geometry

# Compiler
CC = gcc
CCFLAGS = -g -Wall

# Folders
# library files
SOURCES = tuple.c gmaths.c
OBJECTS = $(patsubst %.c, obj/%.o, $(SOURCES))
LIBRARY = lib/libgeolib.a

INCLUDE = -I./inc/
MYLIBS = -lgeolib
CLIBS = -lm

TEST_SOURCES = $(wildcard src/test/*.c)
TESTS := $(addprefix bin/, $(notdir $(TEST_SOURCES:.c=)))

EXERCISE_SOURCES = $(wildcard src/exercises/*.c)
EXERCISES := $(addprefix bin/, $(notdir $(EXERCISE_SOURCES:.c=)))

PROG_SOURCES = $(wildcard src/programs/*.c)
PROGRAMS := $(addprefix bin/, $(notdir $(PROG_SOURCES:.c=)))

# rules

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

bin/%: $(EXERCISE_SOURCES) $(TEST_SOURCES)
	$(CC) $(CCFLAGS) $(INCLUDE) -L./lib $< -o $@ $(MYLIBS) $(CLIBS)

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
	@echo Library: $(LIBS)
	@echo Testsources: $(TESTSOURCES)
	@echo Test progs: $(TESTS)
