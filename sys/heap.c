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
	DATE  : 2.1.2025
	FILE  : sys/heap.c

	hight level function for working in heap
*/

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <vnix/heap.h>
#include <vnix/halt.h>
#include <vnix/kerneldef.h>
#include <vnix/mem_table.h>

#include <libk/kstdmem.h>

#define AREA_SIZE kb(4)

struct alloc_entry {
	uint32_t areas_count;
	bool is_free;
};

static struct alloc_entry alloc_entries[HEAP_MAX_ALLOC_ENTRIES];
static size_t alloc_entries_count = 0;

void heap_init(uint32_t mem_upper)
{
	alloc_entries[alloc_entries_count++] = (struct alloc_entry) {
		.areas_count = (mem_upper - MEM_HEAP_START) / AREA_SIZE,
		.is_free     = true,
	};
}

static struct alloc_entry* add_region(uint32_t areas);
static void* get_entry_mem(struct alloc_entry* entry);

void* kmalloc(size_t size)
{
	uint32_t areas            = size / AREA_SIZE + 1;
	struct alloc_entry* entry = add_region(areas);

	if (entry == NULL)
		return NULL;

	entry->is_free = false;

	return get_entry_mem(entry);
}

void kfree(void* mem)
{
	if (mem < (void*) MEM_HEAP_START)
		return;

	for (int i = 0; i < alloc_entries_count; i++) {
		struct alloc_entry* entry = &alloc_entries[i];

		if (get_entry_mem(entry) == mem) {
			entry->is_free = true;
			return;
		}
	}
}

static struct alloc_entry* add_region(uint32_t areas)
{
	struct alloc_entry* separing_entry = NULL;
	struct alloc_entry* new_entry      = NULL;
	int separing_entry_id              = 0;

	for (int i = 0; i < alloc_entries_count; i++) {
		struct alloc_entry* entry = &alloc_entries[i];

		if (entry->areas_count <= areas && entry->is_free) {
			separing_entry    = entry;
			separing_entry_id = i;

			break;
		}
	}

	if (separing_entry == NULL)
		return NULL;

	if (alloc_entries_count + 1 >= HEAP_MAX_ALLOC_ENTRIES)
		return NULL;

	kmemcpy(&alloc_entries[separing_entry_id + 1], &alloc_entries[separing_entry_id],
			sizeof(struct alloc_entry) * (alloc_entries_count - separing_entry_id));

	alloc_entries_count++;

	separing_entry = &alloc_entries[separing_entry_id + 1];
	new_entry      = &alloc_entries[separing_entry_id];

	separing_entry->areas_count  -= areas;
	new_entry->areas_count        = areas;

	return new_entry;
}

static void* get_entry_mem(struct alloc_entry* entry)
{
	void* addr = (void*) MEM_HEAP_START;
	for (struct alloc_entry* i = alloc_entries; i != entry; i = &i[1])
		addr += i->areas_count * AREA_SIZE;

	return addr;
}
