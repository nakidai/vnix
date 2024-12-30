#include <stdbool.h>

#include <arch/asm.h>

#include <vnix/kerneldef.h>
#include <vnix/halt.h>
#include <vnix/kio.h>

attr_noreturn void halt(void)
{
	kputs("Halted.\n");

	while (true)
		hlt();
}
