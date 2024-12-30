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
