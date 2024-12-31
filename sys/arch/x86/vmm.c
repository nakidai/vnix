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
	DATE  : 1.1.2025
	FILE  : sys/arch/x86/vmm.c

	virtual memory managament realisation for x86
*/

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include <libk/kstdmem.h>
#include <libk/itoa.h>

#include <arch/cpu_flags.h>
#include <arch/asm.h>

#include <vnix/vmm.h>
#include <vnix/kerneldef.h>
#include <vnix/mem_table.h>
#include <vnix/kio.h>

static struct vmm_dir_entry* context;

void vmm_init(uint32_t mem)
{
	struct vmm_dir_entry* kernel_page_dir = (void*) MEM_KERNEL_PAGE_START;
	struct vmm_dir_entry* entry;
	char tmp[128];

	kputs("mark ");
	kputs(kitoa(vmm_get_page_by_addr(MEM_END_RESERVED), tmp, 10));
	kputs(" as kernel...");

	for (size_t i = 0; i < vmm_get_page_by_addr(MEM_END_RESERVED); i++) {
		entry = &kernel_page_dir[i];

		entry->read_write      = true;
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

	kputs("mark ");
	kputs(kitoa(VMM_PAGE_DIR_ENTRY_COUNT - vmm_get_page_by_addr(MEM_END_RESERVED), tmp, 10));
	kputs(" as free memory...");

	for (size_t i = vmm_get_page_by_addr(MEM_END_RESERVED); i < VMM_PAGE_DIR_ENTRY_COUNT; i++) {
		entry = &kernel_page_dir[i];

		kmemset(entry, 0, sizeof(struct vmm_dir_entry));
		entry->addr    = vmm_get_addr_by_page(i);
		entry->present = true;
	}

	for (size_t i = vmm_get_page_by_addr(mem) - 1; i < VMM_PAGE_DIR_ENTRY_COUNT; i++) {
		entry = &kernel_page_dir[i];
		kmemset(entry, 0, sizeof(struct vmm_dir_entry));
	}

	vmm_set_vmm_context(kernel_page_dir);
}

void vmm_set_vmm_context(struct vmm_dir_entry* page_dir)
{
	context = page_dir;

	struct cr0_flags cr0_flags = get_cr0_flags();
	cr0_flags.pg = true;
	cr0_flags.pe = true;
	set_cr0_flags(cr0_flags);

	set_cr3((uint32_t) page_dir);
}
