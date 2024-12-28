#ifndef _vnix_heap_h
#define _vnix_heap_h

#include <stddef.h>

#define HEAP_START 0x2000000
#define HEAP_END 0x40000000

struct heap_malloc_header {
	unsigned long size:31;
	unsigned long used:1;
};

void heap_init(void);

void* heap_ksbrk_page(size_t i);

#endif
