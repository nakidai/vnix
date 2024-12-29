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
