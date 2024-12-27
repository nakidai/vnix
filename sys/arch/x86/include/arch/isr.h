#ifndef _vnix_isr_h
#define _vnix_isr_h

#include <stdint.h>
#include <stddef.h>

#include <vnix/kerneldef.h>

#define ISR_MAX_HANDLERS 256

struct isr_data {
	uint32_t gs;
	uint32_t fs;
	uint32_t es;
	uint32_t ds;
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	uint32_t int_num;
	uint32_t eip, cs, eflags, user_esp, ss;
} attr_packed;

typedef void (*isr_handler_f)(struct isr_data*);

extern isr_handler_f isr_handlers[];

void isr_set_handler(size_t i, isr_handler_f handler);
void isr_handle(struct isr_data data);

#endif
