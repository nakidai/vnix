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
	FILE  : sys/dev_console.c

	console device
*/

#include <stdint.h>
#include <stdbool.h>

#include <vnix/dev_console.h>
#include <vnix/fs.h>
#include <vnix/dev_tty.h>
#include <vnix/heap.h>
#include <vnix/kio.h>
#include <vnix/devfs.h>
#include <vnix/vga_term.h>

#include <libk/kstring.h>

static struct fs_node* ttys[DEV_CONSOLE_TTY_COUNT];
static struct fs_node* dev_console = NULL;
static uint32_t crnt_tty           = 0;

static bool open(struct fs_file* file, uint32_t flags);
static void close(struct fs_file* file);
static int32_t read(struct fs_file* file, uint32_t size, uint8_t* buf);
static int32_t write(struct fs_file* file, uint32_t size, uint8_t* buf);

void dev_console_init(void)
{
	for (int i = 0; i < DEV_CONSOLE_TTY_COUNT; i++) {
		struct terminal* term = kmalloc(sizeof(struct terminal));
		vga_term(term);
		ttys[i] = tty_create_dev(i, term);
	}

	dev_console_set_tty(0);

	kputs("Creating /dev/console...");

	struct device device = {0};
	device.type = FSFT_CHAR_DEV;
	kstrcpy(device.name, "console");

	device.open  = open;
	device.close = close;
	device.read  = read;
	device.write = write;

	dev_console = devfs_add_device(&device);

	kok();
}

void dev_console_set_tty(uint32_t num)
{
	struct terminal* terminal_old = ttys[crnt_tty]->private_node_data;
	struct terminal* terminal_new = ttys[num]->private_node_data;
	
	terminal_old->is_active = false;
	terminal_new->is_active = true;

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
	struct fs_node* tty = ttys[crnt_tty];

	return tty->read(file, size, buf);
}

static int32_t write(struct fs_file* file, uint32_t size, uint8_t* buf)
{
	struct fs_node* tty = ttys[crnt_tty];

	return tty->write(file, size, buf);
}
