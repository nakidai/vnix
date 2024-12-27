#include <stddef.h>
#include <stdint.h>

#include <vnix/heap.h>
#include <vnix/vmm.h>
#include <vnix/halt.h>

static void* heap = NULL;

void heap_init(void)
{
	heap = (void*) HEAP_START;
	heap_ksbrk_page(1);
}

void* heap_ksbrk_page(size_t _i)
{
	struct heap_malloc_header* header;
	uint32_t addr;
	
	if (heap + (_i * VMM_PAGE_SIZE) > (void*) HEAP_END)
		return (void*) -1;

	header = (struct heap_malloc_header*) heap;

	for (size_t i = 0; i < _i; i++) {
		addr = vmm_acquire_page();

		if ((int) addr < 0)
			halt();

		vmm_add_page_to_pd(heap, addr, 0);

		heap += VMM_PAGE_SIZE;
	}

	header->size = VMM_PAGE_SIZE * _i;
	header->used = 0;

	return header;
}
