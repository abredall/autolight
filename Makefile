# -*- MakeFile -*-
ifeq ($(PREFIX),)
	PREFIX := /usr/local
endif
PROJECT=autolight

all: src test
.PHONY: src clean install uninstall test

src:
	@ $(MAKE) -C src/

clean:
	@ echo Cleaning autolight source tree
	@ $(MAKE) -C src/ clean
	@ echo Cleaning autolight test tree
	@ $(MAKE) -C test/ clean

test:
	@ $(MAKE) -C test/ test

install: bin/$(PROJECT)
	@ echo Installing to $(DESTDIR)$(PREFIX)/bin...
	@ install -d $(DESTDIR)$(PREFIX)/bin/
	@ install -m 755 bin/$(PROJECT) $(DESTDIR)$(PREFIX)/bin/
	@ echo Done!

uninstall:
	@ echo Uninstalling from $(DESTDIR)$(PREFIX)/bin...
	@ rm -f $(DESTDIR)$(PREFIX)/bin/$(PROJECT)
	@ echo Done!
