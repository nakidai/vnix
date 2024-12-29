#include <stdint.h>

#include <arch/cpu_flags.h>
#include <arch/asm.h>

struct cr0_flags get_cr0_flags(void)
{
	uint32_t cr0           = get_cr0();
	struct cr0_flags flags = *((struct cr0_flags*) &cr0);

	return flags;
}

void set_cr0_flags(struct cr0_flags flags)
{
	uint32_t cr0 = *((uint32_t*) &flags);
	set_cr0(cr0);
}
