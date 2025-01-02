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
	DATE  : 2.1.2025
	FILE  : sys/include/vnix/devfs.h

	dev directory file system
*/

#ifndef _vnix_devfs_h
#define _vnix_devfs_h

#include <vnix/fs.h>

#define DEVFS_MAX_DEVICE_NAME 16
#define DEVFS_MAX_DEVICES 256

struct device {
	char name[DEVFS_MAX_DEVICE_NAME];

	enum fs_file_type type;
	
	read_write_block_f read_block;
	read_write_block_f write_block;

	read_write_f read;
	read_write_f write;

	read_write_test_f read_test;
	read_write_test_f write_test;

	open_f open;
	close_f close;

	ioctl_f ioctl;
	ftrucate_f ftrucate;

	mmap_f mmap;
	munmap_f munmap;

	void* private_data;
};

void devfs_init(void);
struct fs_node* devfs_add_device(struct device* device);

#endif
