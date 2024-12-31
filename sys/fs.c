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
	FILE  : sys/fs.c

	file system realisation
*/

#include <stddef.h>

#include <vnix/fs.h>
#include <vnix/rootfs.h>
#include <vnix/kio.h>
#include <vnix/panic.h>

#include <libk/kstdmem.h>
#include <libk/kstring.h>

static struct fs fses[FS_MAX_FSES];
static struct fs_node* root = NULL;

void fs_init(void)
{
	kmemset(fses, 0, sizeof(fses));
	root = rootfs_init();
	kok();

	if (!fs_mkdir(root, "dev", 0)) panic("Can't create /dev/ directory!\n");
}

bool fs_mkdir(struct fs_node* node, const char* name, uint32_t flags)
{
	char buf[128] = {0};
	if (fs_get_node_path(node, buf, sizeof(buf)) == -1)
		panic("Invalid node in mkdir!\n");

	kputs("Creating directory ");
	kputs(buf);
	kputs(name);
	kputs("/");
	kputs("\n");

	if ((node->node_type & FSFT_MOUNT_POINT) == FSFT_MOUNT_POINT && node->mount_point != NULL &&
			node->mount_point->mkdir != NULL)
		return node->mount_point->mkdir(node->mount_point, name, flags);
	else if ((node->node_type & FSFT_DIR) == FSFT_DIR && node->mkdir != NULL)
		return node->mkdir(node, name, flags);

	return false;
}

int fs_get_node_path(struct fs_node* node, char* buf, size_t size)
{
	if (node == root && size > 1) {
		buf[0] = '/';
		buf[1] = '\0';
	} else if (size <= 1)
		return -1;

	char target_path[128];

	struct fs_node* n = node;
	int char_index    = 127;
	buf[char_index]   = '\0';
	
	while (n != NULL) {
		size_t lenght = kstrlen(n->name);
		char_index   -= lenght;

		if (char_index < 2)
			return -1;

		if (n->parent != NULL) {
			kstrcpy(target_path + char_index, n->name);
			char_index -= 1;
			target_path[char_index] = '/';
		}

		n = n->parent;
	}
	
	size_t len = 127 - char_index;

	if (size < len)
		return -1;

	kstrcpy(buf, target_path + char_index);

	return len;
}