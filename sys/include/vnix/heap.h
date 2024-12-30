#ifndef _vnix_heap_h
#define _vnix_heap_h

#include <stdint.h>
#include <stddef.h>

void heap_init(uint32_t last_page);

void* kmalloc(size_t size);
void kfree(void* mem);

#endif
