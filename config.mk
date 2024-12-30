ARCH = x86

TOOL_PREFIX      = $(ROOT)/cross
TOOL_NAME_PREFIX = i386-elf-

BIN = ./$(TOOL_PREFIX)/bin

CC = $(BIN)/$(TOOL_NAME_PREFIX)gcc
LD = $(BIN)/$(TOOL_NAME_PREFIX)ld

RM = rm -rf
CP = cp

ASFLAGS  = --32 -g
LDFLAGS  = -melf_i386
CFLAGS   = -nostdlib -nodefaultlibs -g
CPPFLAGS = -I $(ROOT)/include

%.o: %.s
	$(AS) -o $@ $< $(ASFLAGS)
