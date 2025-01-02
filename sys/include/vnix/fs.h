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
	FILE  : sys/include/vnix/fs.h

	file system realisation
*/

#ifndef _vnix_fs_h
#define _vnix_fs_h

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#define FS_MAX_NAME 32
#define FS_MAX_FSES 8
#define FS_MAX_NODE_NAME 128

struct fs_node;
struct fs_file;
struct fs_dirent;
struct stat;

typedef bool (*fs_mount_f)(const char*, const char*, uint32_t, void*);
typedef int32_t (*read_write_block_f)(struct fs_node*, uint32_t, uint32_t, uint8_t*) ;
typedef int32_t (*read_write_f)(struct fs_file*, uint32_t, uint8_t*);
typedef bool (*read_write_test_f)(struct fs_file*);
typedef bool (*open_f)(struct fs_file*, uint32_t);
typedef void (*close_f)(struct fs_file*);
typedef int32_t (*unlink_f)(struct fs_node*, uint32_t);
typedef int32_t (*ioctl_f)(struct fs_file*, int32_t, void*);
typedef int32_t (*lseek_f)(struct fs_file*, int32_t, int32_t);
typedef int32_t (*ftrucate_f)(struct fs_file*, int32_t);
typedef int32_t (*stat_f)(struct fs_node*, struct stat*);
typedef struct fs_dirent* (*read_dir_f)(struct fs_node*, uint32_t);
typedef struct fs_node* (*find_dir_f)(struct fs_node*, const char*);
typedef bool (*mkdir_f)(struct fs_node*, const char*, uint32_t);
typedef void* (*mmap_f)(struct fs_file*, uint32_t, uint32_t, uint32_t);
typedef bool (*munmap_f)(struct fs_file*, void*, uint32_t);

struct fs {
	char name[FS_MAX_NAME];
	fs_mount_f mount;
	fs_mount_f mount_check;
};

struct fs_node {
	char name[FS_MAX_NODE_NAME];
	uint32_t mask;
	uint32_t user_id;
	uint32_t group_id;
	uint32_t node_type;
	uint32_t inode;
	uint32_t lenght;
	
	read_write_block_f read_block;
	read_write_block_f write_block;

	read_write_f read;
	read_write_f write;

	read_write_test_f read_test;
	read_write_test_f write_test;

	open_f open;
	close_f close;

	unlink_f unlink;
	ioctl_f ioctl;
	lseek_f lseek;
	ftrucate_f ftrucate;
	stat_f stat;
	
	read_dir_f read_dir;
	find_dir_f find_dir;
	mkdir_f mkdir;

	mmap_f mmap;
	munmap_f munmap;

    	struct fs_node* first_child;
	struct fs_node* next_sibling;
	struct fs_node* parent;
	struct fs_node* mount_point;
	struct fs_node* mount_source;

	void* private_node_data;
};

struct fs_file {
	struct fs_node* node;
	int32_t fd;
	uint32_t flags;
	int32_t offset;
	void* private_data;
};

struct stat {
	uint16_t st_dev;
	uint16_t st_ino;
	uint32_t st_mode;
	uint16_t st_nlink;
	uint16_t st_uid;
	uint16_t st_gid;
	uint16_t st_rdev;
	uint32_t st_size;

	uint32_t st_atime;
	uint32_t st_spare1;
    	uint32_t st_mtime;
	uint32_t t_spare2;
	uint32_t st_ctime;
	uint32_t st_spare3;
	uint32_t st_blksize;
	uint32_t st_blocks;
	uint32_t st_spare4[2];
};

enum fs_file_type {
	FSFT_FILE        = 1,
	FSFT_CHAR_DEV    = 2,
	FSFT_BLOCK_DEV   = 3,
	FSFT_PIPE        = 4,
	FSFT_SYM_LINK    = 5,
	FSFT_SOCKET      = 6,
	FSFT_DIR         = 128,
	FSFT_MOUNT_POINT = 256,
};

struct fs_dirent {
	char name[FS_MAX_NODE_NAME];
	enum fs_file_type type;
	uint32_t inode;
};

void fs_init(void);

bool fs_mkdir(struct fs_node* node, const char* name, uint32_t flags);
int fs_get_node_path(struct fs_node* node, char* buf, size_t size);
struct fs_node* fs_finddir(struct fs_node* node, const char* name);

struct fs_node* fs_get_root(void);

#endif
