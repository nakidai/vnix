#include "vnix/vmm.h"
#include <arch/tss.h>
#include <arch/gdt.h>
#include <arch/idt.h>

#include <vnix/multiboot.h>
#include <vnix/arch_faluts.h>
#include <vnix/interrput.h>

extern void kmain(struct multiboot* header);

void arch_entry(struct multiboot* header)
{
	tss_init();
	gdt_init();
	idt_init();

	interrput_set(8, falut_double_falut);
	interrput_set(13, falut_general_protection_falut);

	vmm_init(header->mem_upper);
	interrput_set(14, falut_double_falut);

	kmain(header);
}
