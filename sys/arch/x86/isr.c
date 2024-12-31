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
	FILE  : sys/arch/x86/isr.c

	hight level interface for interput handling
*/

#include <stddef.h>
#include <stdint.h>

#include <arch/isr.h>

#include <vnix/halt.h>
#include <vnix/panic.h>

isr_handler_f isr_handlers[ISR_MAX_HANDLERS] = {NULL};

void isr_set_handler(size_t i, isr_handler_f handler)
{
	isr_handlers[i] = handler;
}

void isr_handle(struct isr_data data)
{
	uint8_t int_no = data.int_num & 0xff;

	if (isr_handlers[int_no] == NULL)
		panic("Interrput not found!\n");

	isr_handlers[int_no](&data);	
}
