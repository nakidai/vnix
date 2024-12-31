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
	FILE  : sys/arch/x86/vmm.c

	virtual memory managament realisation for x86
*/

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include <libk/kstdmem.h>

#include <arch/cpu_flags.h>
#include <arch/asm.h>

#include <vnix/vmm.h>
#include <vnix/kerneldef.h>
#include <vnix/mem_table.h>

#define VMM_PAGE_DIR_ENTRY_COUNT 0x100000

#define VMM_ENTFLAG_USER 0
#define VMM_ENTFLAG_SUPERVISOR 1

#define VMM_ENTFLAG_4K_PAGE 0
#define VMM_ENTFLAG_4M_PAGE 1

struct dir_entry {
	unsigned int present         : 1;
	unsigned int read_write      : 1;
	unsigned int user_supervisor : 1;
	unsigned int pwt             : 1;
	unsigned int pcd             : 1;
	unsigned int accessed        : 1;
	unsigned int avalidable0     : 1;
	unsigned int page_size       : 1;
	unsigned int avalidable1     : 4;
	unsigned int addr            : 20;
} attr_packed;

static struct dir_entry* context;

void vmm_init(uint32_t mem)
{
	struct dir_entry* kernel_page_dir = (void*) MEM_KERNEL_PAGE_START;

	vmm_create_page_dir(kernel_page_dir, mem);
	vmm_set_vmm_context(kernel_page_dir);
}

void vmm_create_page_dir(void* _dir, uint32_t mem)
{
	struct dir_entry* dir = (struct dir_entry*) _dir;
	struct dir_entry* entry;

	for (size_t i = 0; i < vmm_get_page_by_addr(MEM_END_RESERVED); i++) {
		entry = &dir[i];

		entry->read_write      = false;
		entry->user_supervisor = VMM_ENTFLAG_SUPERVISOR;
		entry->pwt             = false;
		entry->pcd             = false;
		entry->accessed        = true;
		entry->avalidable0     = false;
		entry->page_size       = VMM_ENTFLAG_4K_PAGE;
		entry->avalidable1     = false;
		entry->addr            = vmm_get_addr_by_page(i);
		entry->present         = true;
	}

	for (size_t i = vmm_get_page_by_addr(MEM_END_RESERVED); i < VMM_PAGE_DIR_ENTRY_COUNT; i++) {
		entry = &dir[i];

		entry->read_write      = false;
		entry->user_supervisor = VMM_ENTFLAG_SUPERVISOR;
		entry->pwt             = false;
		entry->pcd             = false;
		entry->accessed        = false;
		entry->avalidable0     = false;
		entry->page_size       = VMM_ENTFLAG_4K_PAGE;
		entry->avalidable1     = false;
		entry->addr            = vmm_get_addr_by_page(i);
		entry->present         = true;
	}

	for (size_t i = vmm_get_page_by_addr(mem) - 1; i < VMM_PAGE_DIR_ENTRY_COUNT; i++) {
		entry = &dir[i];

		entry->present = false;
	}
}

void* vmm_alloc_page(uint32_t page_num)
{
	struct dir_entry* entry = &context[page_num];

	entry->accessed = true;

	return (void*) vmm_get_addr_by_page(page_num);
}

void vmm_dealloc_page(uint32_t page_num)
{
	struct dir_entry* entry = &context[page_num];

	entry->accessed = false;
}

void vmm_map_page(uint32_t page_num, bool read_write, bool user_supervisor, bool present)
{
	struct dir_entry* entry = &context[page_num];

	entry->read_write      = read_write;
	entry->user_supervisor = user_supervisor;
	entry->present         = present;
}

void vmm_create_link(uint32_t start_page, uint32_t count, void* new_addr)
{
	for (size_t i = 0; i < count; i++) {
		struct dir_entry* entry = &context[start_page + i];

		entry->addr = (uint32_t) new_addr + VMM_PAGE_SIZE * i;
	}
}

void vmm_set_vmm_context(void* page_dir)
{
	context = page_dir;

	struct cr0_flags cr0_flags = get_cr0_flags();
	cr0_flags.pg = true;
	cr0_flags.pe = true;
	set_cr0_flags(cr0_flags);

	set_cr3((uint32_t) page_dir);
}
