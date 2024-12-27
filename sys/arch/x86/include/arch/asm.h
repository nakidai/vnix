#ifndef _vnix_asm_h
#define _vnix_asm_h

#include <stdint.h>

#define hlt() asm volatile("hlt")

void outb(uint16_t port, uint8_t value);
void outw(uint16_t port, uint16_t value);

#endif
