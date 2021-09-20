# -*- MakeFile -*-
CC = gcc
PROJECT = autolight
SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:src/%.c=obj/%.o)
ifeq ($(PREFIX),)
	PREFIX := /usr/local
endif

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

install: bin/$(PROJECT)
	@ echo Installing to $(DESTDIR)$(PREFIX)/bin...
	@ install -d $(DESTDIR)$(PREFIX)/bin/
	@ install -m 755 bin/$(PROJECT) $(DESTDIR)$(PREFIX)/bin/
	@ echo Done!

uninstall:
	@ echo Uninstalling from $(DESTDIR)$(PREFIX)/bin...
	@ rm -f $(DESTDIR)$(PREFIX)/bin/$(PROJECT)
	@ echo Done!
