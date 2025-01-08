ROOT = ..
include $(ROOT)/config.mk

CPPFLAGS += -I include

C_SOURCE = main.c \
	   faluts.c \
	   kio.c \
	   panic.c \
	   vga.c \
	   heap.c \
	   fs.c \
	   rootfs.c \
	   devfs.c \
	   vga_kio.c \
	   dev_tty.c \
	   dev_console.c \
	   vga_term.c

C_OBJECTS = $(C_SOURCE:.c=.o)

S_SOURCE =

S_OBJECTS = $(S_SOURCE:.s=.o)

OBJECTS = arch.o $(C_OBJECTS) $(S_OBJECTS) libk.o

.PHONY: all
all: vmvnix

.PHONY: clean
clean:
	$(RM) $(OBJECTS) vmvnix
	$(MAKE) -C arch clean
	$(MAKE) -C libk clean

vmvnix: $(OBJECTS)
	$(LD) -n -T arch/$(ARCH)/linker.ld -o $@ $(OBJECTS) $(LDFLAGS)

arch.o:
	$(MAKE) -C arch
	cp arch/arch.o .

libk.o:
	$(MAKE) -C libk
	cp libk/libk.o .
