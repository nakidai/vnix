ROOT = .
include $(ROOT)/config.mk

.PHONY: kernel
kernel: vnix

.PHONY: kernel_clean
kernel_clean:
	$(RM) vnix
	$(MAKE) -C sys clean

vnix:
	$(MAKE) -C sys
	cp sys/vnix .
