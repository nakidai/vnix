#ifndef _vnix_asm_h
#define _vnix_asm_h

#include <stdint.h>

#define hlt() asm volatile("hlt")

void outb(uint16_t port, uint8_t value);
void outw(uint16_t port, uint16_t value);

void set_cr0(uint32_t value);
void set_cr3(uint32_t value);

uint32_t get_cr0(void);
uint32_t get_cr3(void);

#endif
