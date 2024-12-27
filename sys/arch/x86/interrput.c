#include <arch/isr.h>

#include <vnix/interrput.h>

void interrput_set(size_t i, interrput_handler_f handler)
{
	isr_set_handler(i, (isr_handler_f) handler);
}
