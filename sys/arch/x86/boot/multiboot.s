.section .multiboot_header
multiboot_header_start:
	.align 4

	.long 0x1BADB002
	.long 1 << 0 | 1 << 1 | 1 << 2
	.long -(0x1BADB002 + 1 << 0 | 1 << 1 | 1 << 2)

	.long 0
	.long 0
	.long 0
	.long 0
	.long 0

	.long 0

	.long 1024
	.long 768
	.long 32

multiboot_header_end:
