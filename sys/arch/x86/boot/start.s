.globl _start
.extern arch_entry

.text
_start:
	jmp .

	cli
	movl __stack_top, %esp

	pushl %ebx
	call arch_entry

	cli
	hlt
