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
	FILE  : sys/arch/x86/include/arch/cpu_flags.h

	work with cpu flags
*/

#ifndef _cpu_flags_h
#define _cpu_flags_h

#include <vnix/kerneldef.h>

struct cr0_flags {
	unsigned int pe : 1;
	unsigned int mp : 1;
	unsigned int em : 1;
	unsigned int ts : 1;
	unsigned int et : 1;
	unsigned int ne : 1;

	unsigned int _unused0 : 11;

	unsigned int wp : 1;
	
	unsigned int _unused1 : 2;

	unsigned int am : 1;

	unsigned int _unused2 : 11;

	unsigned int nw : 1;
	unsigned int cd : 1;
	unsigned int pg : 1;

	unsigned int _unused3 : 1;
} attr_packed;

struct cr0_flags get_cr0_flags(void);
void set_cr0_flags(struct cr0_flags flags);

#endif
