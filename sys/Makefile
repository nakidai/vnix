ROOT = ..
include $(ROOT)/config.mk

CPPFLAGS += -I include

C_SOURCE = main.c \
	   arch_faluts.c \
	   gfx.c \
	   heap.c \

C_OBJECTS = $(C_SOURCE:.c=.o)

S_SOURCE =

S_OBJECTS = $(S_SOURCE:.s=.o)

OBJECTS = $(C_OBJECTS) $(S_OBJECTS) arch.o libk.o

.PHONY: all
all: vnix

.PHONY: clean
clean:
	$(RM) $(OBJECTS) kernel.elf
	$(MAKE) -C arch clean
	$(MAKE) -C libk clean

vnix: $(OBJECTS)
	$(LD) -n -T arch/$(ARCH)/linker.ld -o $@ $(OBJECTS) $(LDFLAGS)

arch.o:
	$(MAKE) -C arch
	cp arch/arch.o .

libk.o:
	$(MAKE) -C libk
	cp libk/libk.o .
