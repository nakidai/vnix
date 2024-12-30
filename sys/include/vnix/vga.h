#ifndef _vnix_vga_h
#define _vnix_vga_h

#include <stdint.h>

void vga_put(const char* str);
void vga_put_pos(const char* str, uint32_t x, uint32_t y);
void vga_put_colored(const char* str, uint32_t x, uint32_t y, uint8_t color);

#endif
