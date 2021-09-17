# -*- MakeFile -*-
CC = gcc
PROJECT = autolight
SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)

all: $(PROJECT)
.PHONY: clean run

$(PROJECT): $(OBJECTS)
	$(CC) $^ -o $@ -l m

src/%.o: src/%.c src/*.h
	$(CC) -c $< -o $@

clean:
	@ echo Cleaning src/
	@ rm -f src/*.o

run:
	./$(PROJECT)
