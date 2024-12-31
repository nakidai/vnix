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
	FILE  : sys/heap.c
	TODO  : rewrite this shit

	hight level function for working in heap
*/

#include <stddef.h>
#include <stdint.h>

#include <vnix/heap.h>
#include <vnix/vmm.h>
#include <vnix/halt.h>
#include <vnix/kerneldef.h>
#include <vnix/mem_table.h>

#define ALLOC_INFO_COUNT_IN_PAGE VMM_PAGE_SIZE / sizeof(struct alloc_entry)

struct alloc_entry {
	uint32_t owner_id;
	uint32_t addr;
	uint32_t size;

	uint32_t _pad;
} attr_packed;

static struct alloc_entry* allocs_entries = NULL;
static size_t allocs_page                 = 0;
static size_t allocs_pages_count          = 0;
static size_t allocs_info_count           = 0;

static size_t allocs_data_pages_count = 0;

static struct alloc_entry* add_alloc_info(void);

void heap_init(uint32_t last_page)
{
	allocs_entries = (void*) vmm_get_addr_by_page(last_page);
	allocs_page    = last_page;
}

void* kmalloc(size_t size)
{
	if (size == 0)
		return NULL;

	struct alloc_entry* entry = add_alloc_info();
	entry->size     = size;
	entry->owner_id = 0; // TODO: 0 is system owner id, change it to process id
	
	void* addr = (void*) MEM_HEAP_START;
	for (int i = 0; i < allocs_info_count - 1; i++) {
		struct alloc_entry* entry = &allocs_entries[-i];

		if (entry->addr == 0)
			continue;

		addr += entry->size;
	}

	if (vmm_get_page_by_addr(((uint32_t) addr - MEM_HEAP_START)) >= allocs_data_pages_count) {
		vmm_alloc_page(vmm_get_page_by_addr(MEM_HEAP_START) + allocs_data_pages_count);
		allocs_data_pages_count++;
	}

	entry->addr = (uint32_t) addr;

	return addr;
}

void kfree(void* mem)
{
	// TODO: ignre, write later
}

static struct alloc_entry* add_alloc_info(void)
{
	for (int i = 0; i < allocs_info_count; i++) {
		struct alloc_entry* entry = &allocs_entries[-i];

		if (entry->addr == 0)
			return entry;
	}

	if (allocs_info_count - (allocs_pages_count *
				ALLOC_INFO_COUNT_IN_PAGE) >= ALLOC_INFO_COUNT_IN_PAGE) {
		allocs_page--;
		allocs_pages_count++;
		vmm_alloc_page(allocs_page);
	}

	allocs_info_count++;
	return &allocs_entries[-allocs_info_count];

	// TODO: deleate pages from alloc info
}
