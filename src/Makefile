# -*- MakeFile -*-
CC = gcc
CFLAGS = -fPIC
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
EXTS = objects/*.o

all: print_message ../bin/autolight test
.PHONY: print_message clean test

print_message:
	@ echo Compiling autolight library
	@ echo C Compiler: $(CC)
	@ echo CFLAGS: $(CFLAGS)
	@ echo Compiling autolight/src/

../bin/autolight: $(OBJECTS)
	@ $(MAKE) -C objects/
	@ $(CC) *.o $(EXTS) -o $@ -l m

%.o: %.c *.h
	@ $(CC) $(CFLAGS) -c $< -o $@

test: test/test
	@ echo Running tests...
	@ test/test

test/test: config.o test/test.o objects/test/*.o
	@ $(CC) config.o test/test.o objects/test/*.o -o test/test

test/test.o: test/test.c
	@ $(CC) $(CFLAGS) -c test/test.c -o test/test.o

objects/test/%.o: objects/test/%.c objects/test/%.h
	@ $(MAKE) -C objects/test

clean:
	@ echo Cleaning autolight/src/
	@ rm -f *.o
	@ rm -f *.so
	@ rm -f test/*.o
	@ rm -f test/test
	@ $(MAKE) -C objects/ clean
