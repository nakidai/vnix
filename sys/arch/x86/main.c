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
	FILE  : sys/arch/x86/main.c

	main arch dependent entry
*/

#include <arch/gdt.h>
#include <arch/idt.h>

#include <vnix/multiboot.h>
#include <vnix/arch_faluts.h>
#include <vnix/interrput.h>
#include <vnix/vga.h>
#include <vnix/kio.h>
#include <vnix/vga_kio.h>
#include <vnix/mem_table.h>

#include <libk/itoa.h>

extern void kernel_entry(struct multiboot* header);

void arch_entry(struct multiboot* header)
{
	interrput_set(8, falut_double_falut);

	vga_kio_init();
	kputs("Booting vnix.\n");
	kprintf("Avalidabe %u bytes memory.\n", kb(header->mem_upper));

	kputs("Initing GDT...");
	gdt_init();
	interrput_set(13, falut_general_protection_falut);
	kok();

	kputs("Initing IDT...");
	idt_init();
	kok();

	kernel_entry(header);
}
