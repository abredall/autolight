# -*- MakeFile -*-
CC 			:= gcc
CFLAGS 	:= -fPIC
TEST_SOURCES := $(wildcard *test*.c)
# SOURCES := $(filter-out $(TEST_SOURCES),$(wildcard *.c))
SOURCES := $(wildcard *.c)
# TEST_HEADERS := $(wildcard *test*.h)
HEADERS := $(wildcard *.h)
# TEST_OBJECTS := $(TEST_SOURCES:.c=.o)
OBJECTS := $(SOURCES:.c=.o)
# TEST_SUBDIRS := $(wildcard *test/)
SUBDIRS	:= $(wildcard */)

all: print_message ../bin/autolight

.PHONY: print_message
print_message:
	@ echo Compiling autolight library
	@ echo C Compiler: $(CC)
	@ echo CFLAGS: $(CFLAGS)
	@ echo Compiling autolight/src/

../bin/autolight: $(OBJECTS) $(SUBDIRS)
	$(CC) $(filter-out ./test.o,$(shell find . -name "*.o")) -o $@ -l m

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: test
test:
	@ $(CC) $(filter-out ./autolight.o,$(shell find . -name "*.o")) -o $@ -l m
	@ ./test

$(TEST_SUBDIRS):
	@ echo $(TEST_SUBDIRS)
	$(MAKE) -C $@

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
