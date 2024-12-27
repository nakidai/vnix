#include <stddef.h>
#include <stdint.h>

#include <arch/isr.h>

#include <vnix/halt.h>

isr_handler_f isr_handlers[ISR_MAX_HANDLERS] = {NULL};

void isr_set_handler(size_t i, isr_handler_f handler)
{
	isr_handlers[i] = handler;
}

void isr_handle(struct isr_data data)
{
	uint8_t int_no = data.int_num & 0xff;

	if (isr_handlers[int_no] == NULL)
		halt();

	isr_handlers[int_no](&data);	
}
