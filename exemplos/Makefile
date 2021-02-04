SUBDIRS=	01-hello \
		

all:
	for d in $(SUBDIRS); do $(MAKE) -C $$d; done

flash:
	for d in $(SUBDIRS); do $(MAKE) -C $$d; done

clean:
	for d in $(SUBDIRS); do $(MAKE) clean -C $$d; done