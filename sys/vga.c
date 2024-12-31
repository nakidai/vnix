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
	DATE  : 31.12.2024
	FILE  : sys/vga.c

	vga interface
*/

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
