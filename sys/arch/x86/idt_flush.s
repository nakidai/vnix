.globl idt_flush
.text
idt_flush:
	movl 4(%esp), %eax
	lidt (%eax)
	ret
