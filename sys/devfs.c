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
	FILE  : sys/devfs.c

	dev directory file system
*/

#include <stddef.h>

#include <vnix/devfs.h>
#include <vnix/heap.h>
#include <vnix/fs.h>
#include <vnix/panic.h>

#include <libk/kstdmem.h>
#include <libk/kstring.h>

static struct fs_node* dev_root = NULL;

static struct fs_node* devices[DEVFS_MAX_DEVICES];
static size_t device_count = 0;

static bool open(struct fs_file* file, uint32_t flags);
static void close(struct fs_file* file);
static struct fs_dirent* readdir(struct fs_node* node, uint32_t index);
static struct fs_node* finddir(struct fs_node* node, const char* name);

void devfs_init(void)
{
	dev_root = kmalloc(sizeof(struct fs_node));
	kmemset(dev_root, 0, sizeof(struct fs_node));

	dev_root->node_type = FSFT_DIR | FSFT_MOUNT_POINT;

	struct fs_node* root = fs_get_root();
	struct fs_node* dev  = fs_finddir(root, "dev");

	if (dev == NULL)
		panic("Directory /dev/ not exsists.\n");

	dev->mount_point = dev_root;
	dev_root->parent = dev->parent;
	kstrcpy(dev_root->name, dev->name);

	dev_root->open     = open;
	dev_root->close    = close;
	dev_root->find_dir = finddir;
	dev_root->read_dir = readdir;
}

struct fs_node* devfs_add_device(struct device* device)
{
	for (int i = 0; i < device_count; i++) {
		struct fs_node* dev_node = devices[i];

		if (kstrcmp(dev_node->name, device->name))
			return NULL;
	}

	struct fs_node* node = kmalloc(sizeof(struct fs_node));
	kmemset(node, 0, sizeof(struct fs_node));

	node->node_type	= device->type;
	
	node->read_block  = device->read_block;
	node->write_block = device->write_block;

	node->read  = device->read;
	node->write = device->write;

	node->read_test  = device->read_test;
	node->write_test = device->write_test;

	node->open  = device->open;
	node->close = device->close;

	node->ioctl    = device->ioctl;
	node->ftrucate = device->ftrucate;

	node->mmap   = device->mmap;
	node->munmap = device->munmap;

	node->private_node_data = device->private_data;
	node->parent            = dev_root;

	devices[device_count++] = node;

	return node;
}

static bool open(struct fs_file* file, uint32_t flags)
{
	return true;
}

static void close(struct fs_file* file)
{
}

static struct fs_dirent dirent;

static struct fs_dirent* readdir(struct fs_node* node, uint32_t index)
{
	struct fs_dirent* out = NULL;

	for (int i = 0; i < device_count; i++) {
		struct fs_node* dev_node = devices[i];

		if (i != index)
			continue;

		kstrcpy(dirent.name, dev_node->name);
		dirent.type  = dev_node->node_type;
		dirent.inode = i;
		out          = &dirent;

		break;
	}

	return out;
}

static struct fs_node* finddir(struct fs_node* node, const char* name)
{
	struct fs_node* out = NULL;

	for (int i = 0; i < device_count; i++) {
		struct fs_node* dev_node = devices[i];

		if (!kstrcmp(dev_node->name, name))
			continue;

		out = dev_node;
		break;
	}

	return out;
}
