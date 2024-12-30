#include <vnix/multiboot.h>
#include <vnix/halt.h>
#include <vnix/interrput.h>
#include <vnix/vmm.h>

void kernel_entry(struct multiboot* args)
{
	halt();
}
