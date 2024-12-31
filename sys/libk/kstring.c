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
	FILE  : sys/libk/kstring.c

	work with strings
*/

#include <stddef.h>

#include <libk/kstring.h>
#include <libk/kstdmem.h>

size_t kstrlen(const char* str)
{
	size_t i      = 0;
	const char* c = str;

	for (; *c != '\0'; c++, i++);

	return i;
}

void kstrcpy(char* dest, const char* src)
{
	kmemcpy(dest, src, kstrlen(src));
}

bool kstrcmp(const char* str0, const char* str1)
{
	if (kstrlen(str0) != kstrlen(str1))
		return false;

	for (int i = 0; i < kstrlen(str0); i++)
		if (str0[i] != str1[i])
			return false;

	return true;
}
