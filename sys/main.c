#include <vnix/multiboot.h>
#include <vnix/halt.h>
#include <vnix/interrput.h>
#include <vnix/vmm.h>
#include <vnix/mem_table.h>
#include <vnix/kio.h>
#include <vnix/heap.h>

void kernel_entry(struct multiboot* args)
{
	kputs("Initing heap...");
	heap_init(vmm_get_page_by_addr(args->mem_upper * 1024) - 1);
	kok();

	kputs("Base initing complete!\n");
	kputs("Kernel build at " __DATE__ " " __TIME__ ".\n");

	halt();
}
