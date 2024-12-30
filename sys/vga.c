#include <stdint.h>

#include <vnix/vga.h>
#include <vnix/kio.h>

#include <libk/kstdmem.h>

static uint32_t term_size;

static char* vga = (char*) 0xb8000;

static uint32_t crnt_x = 0;
static uint32_t crnt_y = 0;

void vga_init(uint32_t size)
{
	term_size = size;
	vga_clear();
}

static void vga_kio_handler(char c);

void vga_init_term(uint32_t size)
{
	vga_init(size);
	kio_set(vga_kio_handler);
}

static void vga_kio_handler(char c)
{
	if (crnt_x >= term_size) {
		crnt_x = 0;
		crnt_y++;
	}

	switch (c) {
	case '\n':
		vga_kio_handler('\r');
		crnt_y++;

		return;
	
	case '\r':
		crnt_x = 0;

		return;

	case '\?':
		crnt_x++;

		return;

	default:
		vga[(crnt_y * term_size + crnt_x) * 2]       = c;
		vga[((crnt_y * term_size + crnt_x) * 2) + 1] = 0x07;

		break;
	}

	crnt_x++;
}

void vga_clear(void)
{
	kmemset(vga, 0, 25 * term_size * 2);
}
