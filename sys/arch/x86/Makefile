ROOT = ../../..
include $(ROOT)/config.mk

SOURCE_S = idt_flush.s \
	   isr_int.s

SOURCE_ASM = gdt_flush.asm

SOURCE_C = asm.c \
	   gdt.c \
	   halt.c \
	   idt.c \
	   interrput.c \
	   isr.c \
	   cpu_flags.c \
	   main.c

CPPFLAGS += -I include -I $(ROOT)/sys/include

OBJECTS = boot.o $(SOURCE_S:.s=.o) $(SOURCE_C:.c=.o) $(SOURCE_ASM:.asm=.o)

.PHONY: all
all: arch.o

.PHONY: clean
clean:
	$(RM) $(OBJECTS) arch.o
	$(MAKE) -C boot clean

boot.o:
	$(MAKE) -C boot
	cp boot/boot.o .

arch.o: $(OBJECTS)
	$(LD) -r -o $@ $(OBJECTS) $(LDFLAGS)
