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
	FILE  : sys/rootfs.c

	root file system
*/

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include <vnix/rootfs.h>
#include <vnix/fs.h>
#include <vnix/heap.h>

#include <libk/kstdmem.h>
#include <libk/kstring.h>

static bool open(struct fs_file* file, uint32_t flags);
static void close(struct fs_file* file);
static struct fs_dirent* readdir(struct fs_node* node, uint32_t index);
static struct fs_node* finddir(struct fs_node* node, const char* name);
static bool mkdir(struct fs_node* node, const char* name, uint32_t flags);

struct fs_node* rootfs_init(void)
{
	struct fs_node* node = kmalloc(sizeof(struct fs_node));
	kmemset(node, 0, sizeof(struct fs_node));
	node->node_type = FSFT_DIR;
	node->open      = open;
	node->close     = close;
	node->read_dir  = readdir;
	node->find_dir  = finddir;
	node->mkdir     = mkdir;

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
	struct fs_node* n = node->first_child;
	uint32_t i        = 0;

	while (n != NULL) {
		if (index == i) {
			dirent.type  = node->node_type;
			dirent.inode = node->inode;

			kmemcpy(dirent.name, node->name, FS_MAX_NODE_NAME);

			return &dirent;
		}

		n = n->next_sibling;
		i++;
	}

	return NULL;
}

static struct fs_node* finddir(struct fs_node* node, const char* name)
{
	struct fs_node* n = node->first_child;
	while (n != NULL) {
		if (kstrcmp(name, n->name))
			return n;

		n = n->next_sibling;
	}

	return NULL;
}

static bool mkdir(struct fs_node* node, const char* name, uint32_t flags)
{
	struct fs_node* n = node->first_child;
	while (n != NULL) {
		if (kstrcmp(name, n->name))
			return false;

		n = n->next_sibling;
	}

	struct fs_node* new_node = kmalloc(sizeof(struct fs_node));
	kmemset(new_node, 0, sizeof(struct fs_node));

	kstrcpy(new_node->name, name);
	new_node->node_type = FSFT_DIR;
	new_node->open      = open;
	new_node->close     = close;
	new_node->read_dir  = readdir;
	new_node->find_dir  = finddir;
	new_node->mkdir     = mkdir;
	new_node->parent    = node;

	if (node->first_child == NULL)
		node->first_child = new_node;

	else {
		n = node->first_child;
		while (n->next_sibling != NULL)
			n = n->next_sibling;

		n->next_sibling = new_node;
	}

	return true;
}
