#include <stdint.h>

#include <libk/kstdmem.h>

#include <arch/tss.h>

#include <vnix/kerneldef.h>

struct tss {
	uint16_t previous_task, __previous_task_unused;
	uint32_t esp0;
	uint16_t ss0, __ss0_unused;
	uint32_t esp1;
	uint16_t ss1, __ss1_unused;
	uint32_t esp2;
	uint16_t ss2, __ss2_unused;
	uint32_t cr3;
	uint32_t eip, eflags, eax, ecx, edx, ebx, esp, ebp, esi, edi;
	uint16_t es, __es_unused;
	uint16_t cs, __cs_unused;
	uint16_t ss, __ss_unused;
	uint16_t ds, __ds_unused;
	uint16_t fs, __fs_unused;
	uint16_t gs, __gs_unused;
	uint16_t ldt_selector, __ldt_sel_unused;
	uint16_t debug_flag, io_map;
} attr_packed;

static struct tss tss;

struct tss_addr tss_addr;

void tss_init(void)
{
	kmemset(&tss, 0, sizeof(struct tss));

	tss.debug_flag = 0x00;
	tss.io_map     = 0x00;
	tss.esp0       = 0;
	tss.ss0        = 0x10;
	tss.cs         = 0x0b;
	tss.ss         = 0x13;
	tss.ds         = 0x13;
	tss.es         = 0x13;
	tss.fs         = 0x13;
	tss.gs         = 0x13;

	tss_addr.base  = (uint32_t) (uint64_t) &tss;
	tss_addr.limit = sizeof(tss);
}
