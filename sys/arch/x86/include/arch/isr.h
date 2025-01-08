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
	FILE  : sys/arch/x86/include/arch/isr.h

	hight level interface for interput handling
*/

#ifndef _vnix_isr_h
#define _vnix_isr_h

#include <stddef.h>

#include <vnix/kerneldef.h>
#include <vnix/interrput.h>

#define ISR_MAX_HANDLERS 256

typedef void (*isr_handler_f)(struct isr_data*);

extern isr_handler_f isr_handlers[];

void isr_set_handler(size_t i, isr_handler_f handler);
void isr_handle(struct isr_data data);

#endif
