.globl _start
.extern start

.section .multiboot_header
_start:
	jmp start

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

	.long 1

	.long 640
	.long 480
	.long 16

multiboot_header_end:
