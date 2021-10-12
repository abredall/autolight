# -*- MakeFile -*-
CC = gcc
CFLAGS = -fPIC
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
EXTS = objects/*.o

.PHONY: print_message clean test

test: tests
	@ echo Testing autolight library...
	@ ./tests

tests: $(OBJECTS) ../src/config.o
	@ $(MAKE) -C objects/
	@ $(CC) *.o $(EXTS) ../src/config.o -o $@ -l m

%.o: %.c *.h
	@ $(CC) $(CFLAGS) -c $< -o $@

../src/config.o: ../src/config.c
	@ $(CC) $(CFLAGS) -c $< -o $@

clean:
	@ echo Cleaning autolight/test
	@ rm -f *.o
	@ rm -f *.so
	@ rm -f tests
	@ $(MAKE) -C objects/ clean
