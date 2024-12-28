.text

.macro push_regs x
	pushfl
	pushl $\x
	pushal
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs

	pushl %ebx
	movw $0x10, %bx
	movw %bx, %ds
	movw %bx, %es
	movw %bx, %fs
	movw %bx, %gs
	popl %ebx
.endm

.macro create_isr x
	.globl isr\x
	isr\x:
		push_regs \x
		call handle
.endm

create_isr 8
create_isr 13
create_isr 14

.macro pop_regs
	popl %gs 
	popl %fs 
	popl %es 
	popl %ds 
	popal
	add $4, %esp
	popfl
.endm

.extern isr_handle

handle:
	call isr_handle
	pop_regs
	iret
