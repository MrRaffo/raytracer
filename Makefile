# compiler
CC = gcc

# compiler flags
CFLAGS = -g -Wall

# my library
LIBDIR = -L./lib

# libraries
MYLIBS = -lgeolib
CLIBS = -lm

# object files
OBJS = obj/tuple.o obj/gmaths.o

# headers
HEADERS = -I./inc/

#output file
OUTPUT = $(INPUT:.c=)

all: $(INPUT) lib
	$(CC) $(INPUT) $(FLAGS) $(HEADERS) $(LIBDIR) -o $(OUTPUT) $(CLIBS) $(MYLIBS)
	
lib: $(OBJS)
	# ar rcs lib/libgeolib.a obj/tuple.o obj/gmaths.o
	ar rcs lib/libgeolib.a $(OBJS)
	
obj/tuple.o:
	gcc -c src/geometry/tuple.c -I./inc/ -o obj/tuple.o
	
obj/gmaths.o:
	gcc -c src/geometry/gmaths.c -I./inc/ -o obj/gmaths.o $(CLIBS)
	
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
