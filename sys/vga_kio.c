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
