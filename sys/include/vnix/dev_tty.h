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
	FILE  : sys/include/vnix/dev_tty.h

	tty device and terminal subsystem
*/

#ifndef _vnix_dev_tty_h
#define _vnix_dev_tty_h

#include <stdint.h>
#include <stdbool.h>

#include <vnix/fs.h>

typedef void (*tty_putchar_f)(char c);
typedef char (*tty_getchar_f)(void);
typedef void (*tty_clear_f)(void);
typedef void (*tty_set_cursor)(uint32_t, uint32_t);

struct terminal {
	uint32_t w, h;
	uint32_t x, y;

	uint32_t buf_pos;
	char* buf;

	tty_putchar_f putchar;
	tty_getchar_f getchar;
	tty_clear_f clear;
	tty_set_cursor set_cursor;

	bool is_active;
};

void tty_create(struct terminal* terminal, uint32_t width, uint32_t height);
struct fs_node* tty_create_dev(int num, struct terminal* terminal);

void tty_switch(struct terminal* term);

#endif
