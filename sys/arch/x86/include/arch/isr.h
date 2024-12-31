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
	FILE  : sys/arch/x86/include/arch/isr.h

	hight level interface for interput handling
*/

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
