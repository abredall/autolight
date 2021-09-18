# -*- MakeFile -*-
CC = gcc
PROJECT = autolight
SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:src/%.c=obj/%.o)

all: bin/$(PROJECT)
.PHONY: clean run

bin/$(PROJECT): $(OBJECTS)
	$(CC) $^ -o $@ -l m

obj/%.o: src/%.c src/*.h
	$(CC) -c $< -o $@

clean:
	@ echo Cleaning src/
	@ rm -f src/*.o

run:
	bin/$(PROJECT)
