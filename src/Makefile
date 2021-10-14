# -*- MakeFile -*-
CC 			:= gcc
CFLAGS 	:= -fPIC
SOURCES := $(wildcard *.c)
HEADERS := $(wildcard *.h)
OBJECTS := $(SOURCES:.c=.o)
SUBDIRS	:= $(wildcard */)

all: print_message ../bin/autolight

.PHONY: print_message
print_message:
	@ echo Compiling autolight library...
	@ echo C Compiler: $(CC)
	@ echo CFLAGS: $(CFLAGS)
	@ echo Compiling autolight/src/

../bin/autolight: $(OBJECTS) $(SUBDIRS)
	@ echo Building autolight binary...
	@ $(CC) $(filter-out ./test.o,$(shell find . -name "*.o")) -o $@ -l m
	@ echo Done!

%.o: %.c $(HEADERS)
	@ $(CC) $(CFLAGS) -c $< -o $@

.PHONY: $(SUBDIRS)
$(SUBDIRS):
	@ $(MAKE) -C $@

.PHONY: test
test:
	@ $(CC) $(filter-out ./autolight.o,$(shell find . -name "*.o")) -o $@ -l m
	@ ./test

.PHONY: clean
clean:
	@ echo Cleaning autolight/src/
	@ rm -f *.o
	@ rm -f test
	@ for i in $(OBJECTS); do \
		rm -f $$i; \
		done
	@ for i in $(SUBDIRS); do \
		$(MAKE) -C $$i clean; \
		done
	@ echo Done!
