.globl start
.extern arch_entry

.text
start:
	cli
	movl $(__stack + 0x4000), %esp
	
	pushl %ebx
	call arch_entry

	cli
	hlt

.section .bss
.comm __stack, 0x4000, 4
