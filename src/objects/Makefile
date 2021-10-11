# -*- MakeFile -*-
CC = gcc
CFLAGS = -fPIC
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

all: print_message $(OBJECTS) tests
.PHONY: print_message tests clean

print_message:
	@ echo Compiling autolight/src/objects/

%.o: %.c *.h
	@ $(CC) $(CFLAGS) -c $< -o $@

tests:
	@ echo Running tests...

clean:
	@ echo Cleaning autolight/src/objects/
	@ rm -f *.o
