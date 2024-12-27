.globl gdt_flush
.text
gdt_flush:
	movl 4(%esp), %eax
	lgdt (%eax)

	movw $0x10, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	movw %ax, %ss

	movl .flush, %eax
	add $0x08, %eax
	jmpl %eax

	.flush:
		ret
