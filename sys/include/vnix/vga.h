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
	FILE  : sys/include/vnix/vga.h

	vga interface
*/

#ifndef _vnix_vga_h
#define _vnix_vga_h

#include <stdbool.h>
#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

void vga_clear(void);

void vga_set_cursor_visible(bool visible);
void vga_add_char(char c, uint8_t color);

void vga_move_cursor(uint32_t x, uint32_t y);
uint32_t vga_get_cursor_x(void);
uint32_t vga_get_cursor_y(void);

#endif
