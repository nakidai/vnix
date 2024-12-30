.globl gdt_flush
.text
gdt_flush:
	movl 4(%esp), %eax

	lgdt (%eax)

	jmp .flush

	.flush:
		ret
