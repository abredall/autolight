# -*- MakeFile -*-
CC = gcc
CFLAGS = -fPIC
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

all: print_message $(OBJECTS)
.PHONY: print_message clean

print_message:
	@ echo Compiling autolight/test/objects/test

%.o: %.c *.h
	@ $(CC) $(CFLAGS) -c $< -o $@

clean:
	@ echo Cleaning autolight/src/objects/test
	@ rm -f *.o
