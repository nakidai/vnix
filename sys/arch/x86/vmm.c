#include <stddef.h>
#include <stdint.h>

#include <libk/kstdmem.h>

#include <vnix/vmm.h>
#include <vnix/heap.h>

static uint32_t* page_dir = (uint32_t*) VMM_PAGE_DIR;
static uint8_t page_frame_bitmap[VMM_PAGE_AREA_SIZE / 8];

static size_t page_count = 0;

void vmm_init(uint32_t mem_kb)
{
	page_count = (mem_kb * 1024) / VMM_PAGE_SIZE;

	for (size_t i = 0; i < page_count; i++)
		page_frame_bitmap[i] = 0;

	for (size_t i = page_count / 8; i < VMM_PAGE_AREA_SIZE / 8; i++)
		page_frame_bitmap[i] = 0xff;

	for (size_t i = vmm_page_from_addr(0x0); i < vmm_page_from_addr(VMM_KERNEL_RESERVED); i++)
		vmm_page_set_used(page_frame_bitmap, i);

	for (size_t i = 0; i < 4; i++)
		page_frame_bitmap[i] = (i * VMM_PAGE_SIZE_4M | (VMM_PG_PRESENT | VMM_PG_WRITE | VMM_PG_4M));

	for (size_t i = 4; i < 1024; i++)
		page_frame_bitmap[i] = 0;

	page_frame_bitmap[1023] = page_count | VMM_PG_PRESENT | VMM_PG_WRITE;

	kmemset((void*) VMM_PD_AREA_START, 0, VMM_PD_AREA_END - VMM_PD_AREA_START);

	asm(
			"mov %0, %%eax\n"
			"mov %%eax, %%cr3\n"
			"mov %%cr4, %%eax\n"
			"or %2, %%eax\n"
			"mov %%eax, %%cr4\n"
			"mov %%cr0, %%eax\n"
			"or %1, %%eax\n"
			"mov %%eax, %%cr0\n"
			::
			"m"(page_dir),
			"i"(VMM_PAGING_FLAG),
			"i"(VMM_PSE_FLAG)
	);

	heap_init();
}

uint32_t vmm_acquire_page(void)
{
	uint32_t page = -1;

	for (size_t byte = 0; byte < VMM_PAGE_AREA_SIZE; byte++) {
		if (page_frame_bitmap[byte] == 0xff)
			continue;

		for (uint8_t bit; bit < 8; bit++) {
			page = 8 * page + bit;
			vmm_page_set_used(page_frame_bitmap, page);

			return page * VMM_PAGE_SIZE;
		}
	}

	return -1;
}

static uint32_t read_cr3(void);
static void sync_all_from_kernel(void);

bool vmm_add_page_to_pd(void* v_addr, uint32_t p_addr, int flags)
{
	int pd_index = (((uint32_t) v_addr) >> 22);
	int pt_index = (((uint32_t) v_addr) >> 12) & 0x03ff;

	uint32_t* pd = (uint32_t*) 0xfffff000;
	uint32_t* pt = ((uint32_t*) 0xffc00000) + (0x400 + pd_index);

	uint32_t cr3 = 0;

	if (v_addr < (void*) HEAP_END) {
		cr3 = read_cr3();
		asm(
			"mov %0, %%eax\n"
			"mov %%eax, %%cr3\n"
			::
			"m"(pd)
		);
	}

	if ((pd[pd_index] & VMM_PG_PRESENT) != VMM_PG_PRESENT) {
		uint32_t phys_table = vmm_acquire_page();
		pd[pd_index] = phys_table | (flags & 0xfff) | (VMM_PG_PRESENT | VMM_PG_WRITE);

		asm(
			"invlpg %0\n"
			::
			"m"(v_addr)
		);

		for (size_t i = 0; i < 1024; i++)
			pt[i] = 0;
	}

	if ((pt[pt_index] & VMM_PG_PRESENT) == VMM_PG_PRESENT) {
		if (cr3 != 0)
			asm(
				"mov %0, %%eax\n"
				"mov %%eax, %%cr3\n"
				::
				"m"(pd)
			);

		return false;
	}

	pt[pt_index] = p_addr | (flags & 0xfff) | (VMM_PG_PRESENT | VMM_PG_WRITE);

	asm(
		"invlpg %0\n"
		::
		"m"(v_addr)
	);

	if (cr3 != 0)
		asm(
			"mov %0, %%eax\n"
			"mov %%eax, %%cr3\n"
			::
			"m"(pd)
		);

	if (v_addr < (void*) HEAP_END)
		sync_all_from_kernel();

	return true;
}

static uint32_t read_cr3(void)
{
	uint32_t value;
	asm volatile(
		"mov %%cr3, %0\n"
		:
		"=r" (value)
	);

	return value;
}

static void sync_all_from_kernel(void)
{
	for (uint32_t addr = VMM_PD_AREA_START; addr < VMM_PD_AREA_END; addr += VMM_PAGE_SIZE) {
		uint32_t* pd = (uint32_t*) addr;

		if ((void*) *pd != NULL) for (size_t i = 0; i < VMM_KERNEL_PAGE_COUNT; i++)
			pd[i] = page_dir[i] & ~VMM_PG_OWNED;
	}
}
