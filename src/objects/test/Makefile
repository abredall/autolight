# -*- MakeFile -*-
CC 			:= gcc
CFLAGS 	:= -fPIC
SOURCES := $(wildcard *.c)
HEADERS	:= $(wildcard *.h)
OBJECTS := $(SOURCES:.c=.o)
SUBDIRS	:= $(wildcard */)

all: print_message $(OBJECTS) $(SUBDIRS)

.PHONY: print_message
print_message:
	@ echo Compiling autolight/src/objects/test/

%.o: %.c $(HEADERS)
	@ $(CC) $(CFLAGS) -c $< -o $@

.PHONY: $(SUBDIRS)
$(SUBDIRS):
	@ $(MAKE) -C $@

.PHONY: clean
clean:
	@ echo Cleaning autolight/src/objects/test/
	@ for i in $(OBJECTS); do \
		rm -f $$i; \
		done
	@ for i in $(SUBDIRS); do \
		$(MAKE) -C $$i clean; \
		done
