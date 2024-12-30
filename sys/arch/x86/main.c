#include <arch/tss.h>
#include <arch/gdt.h>
#include <arch/idt.h>

#include <vnix/multiboot.h>
#include <vnix/arch_faluts.h>
#include <vnix/interrput.h>
#include <vnix/vmm.h>
#include <vnix/vga.h>

extern void kernel_entry(struct multiboot* header);

void arch_entry(struct multiboot* header)
{
	vga_put("Booting vnix.");

	tss_init();
	gdt_init();
	idt_init();

	interrput_set(8, falut_double_falut);
	interrput_set(13, falut_general_protection_falut);
	interrput_set(14, falut_page_falut);

	vmm_init(header->mem_upper);

	kernel_entry(header);
}
