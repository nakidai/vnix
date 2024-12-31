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
	FILE  : sys/arch/x86/cpu_flags.c

	work with cpu flags
*/

#include <stdint.h>

#include <arch/cpu_flags.h>
#include <arch/asm.h>

struct cr0_flags get_cr0_flags(void)
{
	uint32_t cr0           = get_cr0();
	struct cr0_flags flags = *((struct cr0_flags*) &cr0);

	return flags;
}

void set_cr0_flags(struct cr0_flags flags)
{
	uint32_t cr0 = *((uint32_t*) &flags);
	set_cr0(cr0);
}
