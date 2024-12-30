#include <arch/tss.h>
#include <arch/gdt.h>
#include <arch/idt.h>

#include <vnix/multiboot.h>
#include <vnix/arch_faluts.h>
#include <vnix/interrput.h>
#include <vnix/vmm.h>
#include <vnix/vga.h>
#include <vnix/kio.h>

extern void kernel_entry(struct multiboot* header);

void arch_entry(struct multiboot* header)
{
	vga_init_term(80);
	kputs("Booting vnix.\n");

	kputs("Initing TSS...");
	tss_init();
	kok();

	kputs("Initing GDT...");
	gdt_init();
	kok();

	kputs("Initing IDT...");
	idt_init();
	kok();

	kputs("Setting up insterrputs...");
	interrput_set(8, falut_double_falut);
	interrput_set(13, falut_general_protection_falut);
	interrput_set(14, falut_page_falut);
	kok();

	kputs("Initing paging...");
	vmm_init(header->mem_upper * 1024);
	kok();

	kputs("Going to kernel.\n");
	kernel_entry(header);
}
