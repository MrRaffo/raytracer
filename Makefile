# compiler
CC = gcc

# compiler flags
CFLAGS = -g -Wall

# my library
LIBDIR = -L./lib

# libraries
MYLIBS = -lgeolib

# headers
HEADERS = -I./inc/

#output file
OUTPUT = $(INPUT:.c=)

all: $(INPUT)
	$(CC) $(INPUT) $(FLAGS) $(HEADERS) $(LIBDIR) -o $(OUTPUT) -lgeolib
	
lib: obj/geometry/tuple.o
	ar rcs lib/libgeolib.a obj/geometry/tuple.o
	
obj/geometry/tuple.o:
	gcc -c src/geometry/tuple.c -I./inc/ -o obj/geometry/tuple.o
	
.PHONY: clean cleanlib cleanall cleanbin

clean: cleanbin cleanobj
	
cleanobj:
	rm -rf obj/*
	
cleanlib:
	rm -rf lib/*
	
cleanbin:
	rm -rf bin/*
	
cleanall: cleanbin cleanlib cleanobj
	rm -rf bin/* obj/* lib/*
