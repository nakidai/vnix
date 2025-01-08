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
	FILE  : sys/arch/x86/asm.c

	function and macroses for using assembly in C
*/

#include <stdint.h>

#include <arch/asm.h>

void outb(uint16_t port, uint8_t value)
{
	asm volatile(
		"outb %1, %0"
		::
		"dN" (port),
		"a" (value)
	);
}

void outw(uint16_t port, uint16_t value)
{
	asm volatile(
		"outw %1, %0"
		::
		"dN" (port),
		"a" (value)
	);
}

uint8_t inb(uint16_t port)
{
	uint8_t value;
	
	asm volatile(
		"inb %1, %0"
		:
		"=a" (value)
		:
		"dN" (port)
	);

	return value;
}

uint16_t ibw(uint16_t port)
{
	uint16_t value;
	
	asm volatile(
		"inw %1, %0"
		:
		"=a" (value)
		:
		"dN" (port)
	);

	return value;
}

void set_cr0(uint32_t value)
{
	asm volatile(
		"mov %0, %%cr0"
		::
		"a" (value)
	);
}

void set_cr3(uint32_t value)
{
	asm volatile(
		"mov %0, %%cr3"
		::
		"a" (value)
	);
}

uint32_t get_cr0(void)
{
	uint32_t value;

	asm volatile(
		"mov %%cr0, %0"
		:
		"=r" (value)
	);

	return value;
}

uint32_t get_cr3(void)
{
	uint32_t value;

	asm volatile(
		"mov %%cr3, %0"
		:
		"=r" (value)
	);

	return value;
}
