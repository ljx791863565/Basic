SUBDIRS=
SUBDIRS +=

all:
	for d in $(SUBDIRS); do [ -d $$d ]  && $(NAKE) -C $$d; done
clean:
	for d in $(SUBDIRS); do [ -d $$d ] && $(MAKE) -C $$d clean; done