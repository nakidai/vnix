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
	FILE  : sys/libk/kstdmem.c

	work with memory
*/

#include <stddef.h>
#include <stdint.h>

#include <libk/kstdmem.h>

void kmemcpy(void* dest, const void* src, size_t n)
{
	uint8_t* dest_uint8      = (uint8_t*) dest;
	const uint8_t* src_uint8 = (uint8_t*) src;

	for (size_t i = 0; i < n; i++)
		dest_uint8[i] = src_uint8[i];
}

void kmemset(void* dest, uint8_t data, size_t n)
{
	uint8_t* dest_uint8 = (uint8_t*) dest;

	for (size_t i = 0; i < n; i++)
		dest_uint8[i] = data;
}
