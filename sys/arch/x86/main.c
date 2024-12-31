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
	FILE  : sys/arch/x86/main.c

	main arch dependent entry
*/

#include <arch/tss.h>
#include <arch/gdt.h>
#include <arch/idt.h>

#include <vnix/multiboot.h>
#include <vnix/arch_faluts.h>
#include <vnix/interrput.h>
#include <vnix/vmm.h>
#include <vnix/vga.h>
#include <vnix/kio.h>

#include <libk/itoa.h>

extern void kernel_entry(struct multiboot* header);

void arch_entry(struct multiboot* header)
{
	vga_init_term(80);
	kputs("Booting vnix.\n");

	char num[128] = {0};
	kitoa(header->mem_upper * 1024, num, 10);
	kputs("Avalidabe ");
	kputs(num);
	kputs(" bytes memory.\n");

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
