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
	FILE  : sys/arch/x86/include/arch/asm.h

	function and macroses for using assembly in C
*/

#ifndef _vnix_asm_h
#define _vnix_asm_h

#include <stdint.h>

#define hlt() asm volatile("hlt")

void outb(uint16_t port, uint8_t value);
void outw(uint16_t port, uint16_t value);

uint8_t inb(uint16_t port);
uint16_t ibw(uint16_t port);

void set_cr0(uint32_t value);
void set_cr3(uint32_t value);

uint32_t get_cr0(void);
uint32_t get_cr3(void);

#endif
