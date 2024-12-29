#include <stdint.h>

#include <arch/asm.h>

#define get_reg(func, reg, type) \
	type func(void) \
	{ \
		type value; \
		asm volatile( \
			"mov %%##reg, %0" \
			:: \
			"i" (value) \
		); \
		return value; \
	}

#define set_reg(func, reg, type) \
	void func(type value) \
	{ \
		asm volatile( \
			"mov %0, %%##reg" \
			:: \
			"i" (value) \
		); \
	}

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

set_reg(set_cr0, cr0, uint32_t);
set_reg(set_cr3, cr3, uint32_t);

get_reg(get_cr0, cr0, uint32_t)
get_reg(get_cr3, cr3, uint32_t)
