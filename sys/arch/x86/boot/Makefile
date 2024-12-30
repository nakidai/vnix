ROOT = ../../../..
include $(ROOT)/config.mk

SOURCE_S = start.s \
	   multiboot.s \

OBJECTS = $(SOURCE_S:.s=.o)

.PHONY: all
all: boot.o

.PHONY: clean
clean:
	$(RM) $(OBJECTS)

boot.o: $(OBJECTS)
	$(LD) -r -o $@ $(OBJECTS) $(LDFLAGS)
