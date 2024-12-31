/*
	Permission to use, copy, modify, and/or distribute this software for
	any purpose with or without fee is hereby granted.

	THE SOFTWARE IS PROVIDED “AS IS” AND THE AUTHOR DISCLAIMS ALL
	WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES
	OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE
	FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY
	DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN
	AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
	OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

/*
	AUTHOR: gimura2022 <gimura0001@gmail.com>
	DATE  : 31.12.2024
	FILE  : sys/arch/x86/isr_int.s

	interrput handling
*/

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
