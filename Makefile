ROOT = .
include $(ROOT)/config.mk

.PHONY: kernel
kernel: vmvnix

.PHONY: kernel_clean
kernel_clean:
	$(RM) vmvnix
	$(MAKE) -C sys clean

vmvnix:
	$(MAKE) -C sys
	cp sys/vmvnix .
