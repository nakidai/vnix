#include <vnix/multiboot.h>
#include <vnix/halt.h>
#include <vnix/interrput.h>
#include <vnix/vmm.h>

void kmain(struct multiboot* args)
{
	halt();
}
