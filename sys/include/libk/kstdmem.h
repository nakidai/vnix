#ifndef _kstdmem_h
#define _kstdmem_h

#include <stddef.h>

void kmemcpy(void* dest, const void* src, size_t n);
void kmemset(void* dest, uint8_t data, size_t n);

#endif
