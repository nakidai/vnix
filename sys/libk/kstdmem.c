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
