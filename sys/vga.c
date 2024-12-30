#include <stdint.h>

#include <vnix/vga.h>

static char* vga    = (char*) 0xb8000;
static uint32_t crnt_y = 0;

void vga_put(const char* str)
{
	vga_put_pos(str, 0, crnt_y++);
}

void vga_put_pos(const char* str, uint32_t x, uint32_t y)
{
	vga_put_colored(str, x, y, 0x07);
}

void vga_put_colored(const char* str, uint32_t x, uint32_t y, uint8_t color)
{
	for (const char* c = str; *c != '\0'; c++) {
		vga[(y * 80 + x) + ((c - str) * 2)]     = *c;
		vga[(y * 80 + x) + ((c - str) * 2) + 1] = color;
	}
}
