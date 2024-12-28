#ifndef _vnix_vmm_h
#define _vnix_vmm_h

#include <stdint.h>
#include <stdbool.h>

#define VMM_PAGE_DIR 0x1000
#define VMM_PAGE_AREA_SIZE 0x100000
#define VMM_KERNEL_RESERVED 0x01000000
#define VMM_KERNEL_PAGE_COUNT 256

#define VMM_PAGE_SIZE 0x00001000
#define VMM_PAGE_SIZE_4M 0x00400000

#define VMM_PG_PRESENT 0x1
#define VMM_PG_WRITE 0x2
#define VMM_PG_USER 0x4
#define VMM_PG_OWNED 0x200
#define VMM_PG_4M 0x80

#define VMM_PD_AREA_START 0x00C00000
#define VMM_PD_AREA_END 0x01000000

#define VMM_PAGING_FLAG 0x80000000
#define VMM_PSE_FLAG 0x10

#define vmm_page_from_addr(x) ((x) >> 12)
#define vmm_page_set_used(m, i) m[((uint32_t) i) / 8] |= (1 << (((uint32_t) i) % 8))

void vmm_init(uint32_t mem_kb);

uint32_t vmm_acquire_page(void);
bool vmm_add_page_to_pd(void* v_addr, uint32_t p_addr, int flags);

#endif
