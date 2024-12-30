#ifndef _vnix_vga_h
#define _vnix_vga_h

#include <stdint.h>

void vga_init_term(uint32_t size);
void vga_init(uint32_t size);

void vga_clear(void);

#endif
