ROOT = ../..
include $(ROOT)/config.mk

CPPFLAGS += -I $(ROOT)/sys/include

SOURCE_C = kstdmem.c

OBJECTS = $(SOURCE_C:.c=.o)

.PHONY: all
all: libk.o

.PHONY: clean
clean:
	$(RM) $(OBJECTS) libk.o

libk.o: $(OBJECTS)
	$(LD) -r -o $@ $(OBJECTS) $(LDFLAGS)
