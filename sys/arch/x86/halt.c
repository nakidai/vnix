#include <stdbool.h>

#include <arch/asm.h>

#include <vnix/kerneldef.h>
#include <vnix/halt.h>

attr_noreturn void halt(void)
{
	while (true)
		hlt();
}
