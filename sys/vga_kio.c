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
	FILE  : sys/vga_kio.c

	vga interface for kernel io
*/

#include <vnix/vga_kio.h>
#include <vnix/kio.h>
#include <vnix/vga.h>

static void kio_handler(char c);

void vga_kio_init(void)
{
	vga_clear();
	vga_set_cursor_visible(false);

	kio_set(kio_handler);
}

static void kio_handler(char c)
{
	switch (c) {
	case '\n':
		kio_handler('\r');
		vga_move_cursor(vga_get_cursor_x(), vga_get_cursor_y() + 1);

		break;

	case '\r':
		vga_move_cursor(0, vga_get_cursor_y());

		break;

	case '\?':
		vga_move_cursor(vga_get_cursor_x() + 1, vga_get_cursor_y());

		break;

	default:
		vga_add_char(c, 0x07);
		vga_move_cursor(vga_get_cursor_x() + 1, vga_get_cursor_y());

		break;
	}
}
