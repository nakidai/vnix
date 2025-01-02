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
	DATE  : 3.1.2025
	FILE  : sys/dev_tty.c

	tty device and terminal subsystem
*/

#include <stdint.h>

#include <vnix/dev_tty.h>
#include <vnix/devfs.h>
#include <vnix/heap.h>
#include <vnix/fs.h>
#include <vnix/kio.h>

#include <libk/kstdmem.h>
#include <libk/kstring.h>
#include <libk/itoa.h>

void tty_create(struct terminal* terminal, uint32_t width, uint32_t height)
{
	kmemset(terminal, 0, sizeof(struct terminal));

	terminal->w = width;
	terminal->h = height;

	terminal->buf = kmalloc(width * height);
	kmemset(terminal->buf, 0, width * height);
}

static bool open(struct fs_file* file, uint32_t flags);
static void close(struct fs_file* file);
static int32_t read(struct fs_file* file, uint32_t size, uint8_t* buf);
static int32_t write(struct fs_file* file, uint32_t size, uint8_t* buf);

struct fs_node* tty_create_dev(int num, struct terminal* terminal)
{
	char buf[128];

	kputs("Creating /dev/tty");
	kputs(kitoa(num, buf, 10));
	kputs("...");

	struct device device = {0};
	kstrcpy(device.name, "tty");
	kstrcpy(device.name + 3, kitoa(num, buf, 10));

	device.open  = open;
	device.close = close;
	device.read  = read;
	device.write = write;

	device.private_data = terminal;
	device.type         = FSFT_CHAR_DEV;

	struct fs_node* node = devfs_add_device(&device);

	kok();

	return node;
}

static void write_to_term_buf(struct terminal* term, char c);
static void putchar_term(struct terminal* term, char c);

void tty_switch(struct terminal* term)
{
	term->clear();

	for (int i = 0; i < term->buf_pos; i++)
		putchar_term(term, term->buf[i]);	
}

static bool open(struct fs_file* file, uint32_t flags)
{
	return true;
}

static void close(struct fs_file* file)
{
}

static int32_t read(struct fs_file* file, uint32_t size, uint8_t* buf)
{
	struct terminal* terminal = file->node->private_node_data;

	if (!terminal->is_active)
		return 0;

	for (int i = 0; i < size; i++) {
		char c = terminal->getchar();

		write_to_term_buf(terminal, c);
		buf[i] = c;

		putchar_term(terminal, c);
	}

	return size;
}

static int32_t write(struct fs_file* file, uint32_t size, uint8_t* buf)
{
	struct terminal* terminal = file->node->private_node_data;

	for (int i = 0; i < size; i++) {
		write_to_term_buf(terminal, buf[i]);

		if (terminal->is_active)
			putchar_term(terminal, buf[i]);
	}

	return size;
}

static void write_to_term_buf(struct terminal* term, char c)
{
	if (term->buf_pos != term->w * term->h) {
		term->buf[term->buf_pos++] = c;
		return;
	}

	kmemcpy(term->buf, term->buf + 1, term->w * term->h - 1);
	term->buf[term->w * term->h - 1] = c;
}

static void putchar_term(struct terminal* term, char c)
{
	switch (c) {
	case '\n':
		putchar_term(term, '\r');

		term->y++;
		term->set_cursor(term->x, term->y);

		break;

	case '\r':
		term->x = 0;
		term->set_cursor(term->x, term->y);

		break;
	
	case '\0':
		break;

	default:
		term->putchar(c);
		term->x++;
		term->set_cursor(term->x, term->y);

		break;
	}
}
