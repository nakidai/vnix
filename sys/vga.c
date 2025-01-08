/*
	Permission to use, copy, modify, and/or distribute this software for
	any purpose with or without fee is hereby granted.

	THE SOFTWARE IS PROVIDED “AS IS” AND THE AUTHOR DISCLAIMS ALL
	WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES
	OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE
	FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY
	DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN
	AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
	OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

/*
	AUTHOR: gimura2022 <gimura0001@gmail.com>
	FILE  : sys/vga.c

	vga interface
*/

#include <stdint.h>

#include <vnix/vga.h>
#include <vnix/kio.h>
#include <vnix/port_io.h>

#include <libk/kstdmem.h>

static char* vga = (char*) 0xb8000;

static uint32_t crnt_x = 0;
static uint32_t crnt_y = 0;

void vga_clear(void)
{
	kmemset(vga, 0, VGA_WIDTH * VGA_HEIGHT * 2);
	crnt_x = 0;
	crnt_y = 0;
}

void vga_set_cursor_visible(bool visible)
{
	uint8_t cursor = inb(0x3d5);

	cursor = visible ? cursor & ~0x20 : cursor | 0x20;

	outb(0x3d5, cursor);
}

void vga_add_char(char c, uint8_t color)
{
	if ((crnt_y * VGA_WIDTH + crnt_x) * 2 == VGA_WIDTH * VGA_HEIGHT * 2) {
		char buf[VGA_WIDTH * (VGA_HEIGHT - 1) * 2];
		kmemcpy(buf, &vga[VGA_WIDTH * 2], VGA_WIDTH * (VGA_HEIGHT - 1) * 2);
		kmemcpy(vga, buf, VGA_WIDTH * (VGA_HEIGHT - 1) * 2);

		kmemset(&vga[(VGA_HEIGHT - 1) * VGA_WIDTH * 2], 0, VGA_WIDTH * 2);

		crnt_y--;
	}

	vga[(crnt_y * VGA_WIDTH + crnt_x) * 2]     = c;
	vga[(crnt_y * VGA_WIDTH + crnt_x) * 2 + 1] = color;
}

void vga_move_cursor(uint32_t x, uint32_t y)
{
	uint16_t cursor_loc = y * VGA_WIDTH + x;

	outb(0x3d4, 14);
	outb(0x3d5, cursor_loc >> 8);
	outb(0x3d4, 15);
	outb(0x3d5, cursor_loc);

	crnt_x = x;
	crnt_y = y;
}

uint32_t vga_get_cursor_x(void)
{
	return crnt_x;
}

uint32_t vga_get_cursor_y(void)
{
	return crnt_y;
}
