ROOT = ../..
include $(ROOT)/config.mk

.PHONY: all
all: arch.o

.PHONY: clean
clean:
	$(RM) arch.o
	$(MAKE) -C $(ARCH) clean

arch.o:
	$(MAKE) -C $(ARCH)
	cp $(ARCH)/arch.o .
