# -*- MakeFile -*-
CC = gcc
CFLAGS = -fPIC
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

all: print_message $(OBJECTS)
.PHONY: print_message tests clean

print_message:
	@ echo Compiling autolight/src/cfg/

%.o: %.c *.h
	@ $(CC) $(CFLAGS) -c $< -o $@

clean:
	@ echo Cleaning autolight/src/cfg/
	@ rm -f *.o
