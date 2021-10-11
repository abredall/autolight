# -*- MakeFile -*-
ifeq ($(PREFIX),)
	PREFIX := /usr/local
endif
PROJECT=autolight

all: src

.PHONY: src
src:
	@ $(MAKE) -C src/

# bin/$(PROJECT): $(OBJECTS)
# 	$(CC) $^ -o $@ -l m

# obj/%.o: src/%.c src/*.h
# 	$(CC) -c $< -o $@

clean:
	@ echo Cleaning autolight source tree
	@ $(MAKE) -C src/ clean

# run:
# 	bin/$(PROJECT)

install: bin/$(PROJECT)
	@ echo Installing to $(DESTDIR)$(PREFIX)/bin...
	@ install -d $(DESTDIR)$(PREFIX)/bin/
	@ install -m 755 bin/$(PROJECT) $(DESTDIR)$(PREFIX)/bin/
	@ echo Done!

uninstall:
	@ echo Uninstalling from $(DESTDIR)$(PREFIX)/bin...
	@ rm -f $(DESTDIR)$(PREFIX)/bin/$(PROJECT)
	@ echo Done!
