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
	FILE  : sys/include/vnix/vmm.h

	virtual memory managament interface
*/

#ifndef _vnix_vmm_h
#define _vnix_vmm_h

#include <stdint.h>
#include <stdbool.h>

#include <vnix/mem_table.h>
#include <vnix/kerneldef.h>

#define VMM_PAGE_DIR_ENTRY_COUNT 0x100000

#define VMM_ENTFLAG_USER 0
#define VMM_ENTFLAG_SUPERVISOR 1

#define VMM_ENTFLAG_4K_PAGE 0
#define VMM_ENTFLAG_4M_PAGE 1

#define VMM_ENTFLAG_READ 0
#define VMM_ENTFLAG_WRITE 1

#define VMM_ENTFLAG_4K_PAGE 0
#define VMM_ENTFLAG_4M_PAGE 1

#define VMM_PAGE_SIZE kb(4)

#define vmm_get_page_by_addr(addr) (addr >> 12)
#define vmm_get_addr_by_page(page) (page << 12)

struct vmm_dir_entry {
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

void vmm_init(uint32_t mem);
void vmm_set_vmm_context(struct vmm_dir_entry* page_dir);

#endif
