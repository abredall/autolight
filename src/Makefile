# -*- MakeFile -*-
CC = gcc
CFLAGS = -fPIC
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
EXTS = objects/*.o io/*.o

all: print_message ../bin/autolight
.PHONY: print_message clean

print_message:
	@ echo Compiling autolight library
	@ echo C Compiler: $(CC)
	@ echo CFLAGS: $(CFLAGS)
	@ echo Compiling autolight/src/

../bin/autolight: $(OBJECTS)
	@ $(MAKE) -C objects/
	@ $(MAKE) -C io/
	@ $(CC) *.o $(EXTS) -o $@ -l m

%.o: %.c *.h
	@ $(CC) $(CFLAGS) -c $< -o $@

clean:
	@ echo Cleaning autolight/src/
	@ rm -f *.o
	@ rm -f *.so
	@ $(MAKE) -C objects/ clean
