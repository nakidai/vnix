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
	FILE  : sys/include/vnix/mem_table.h

	table of memory
*/

#ifndef _vnix_mem_table_h
#define _vnix_mem_table_h

#define kb(x) x * 1024
#define mb(x) kb(x) * 1024
#define gb(x) mb(x) * 1024

/*
 * =============
 * | 0x0       | memory start
 * | --------- |
 * | 1 mb      | not used
 * | --------- |
 * | 0x100000  | 
 * |           |
 * | 0x100000  | 
 * | --------- |
 * | 12 mb     | kernel code
 * | --------- |
 * | 0xd00000  |
 * |           |
 * | 0xd00000  | MEM_KERNEL_PAGE_START
 * | --------- |
 * | 4 mb      | kernel page directory
 * | --------- |
 * | 0x1100000 | MEM_KERNEL_PAGE_END
 * |           |
 * | 0x1100000 |
 * | --------- |
 * | 16 mb     | gfx memory
 * | --------- |
 * | 0x2100000 |
 * |           |
 * | 0x2100000 | end reserved memory
 * | --------- | MEM_END_RESERVED
 * |           |
 * | 0x2100000 | heap start
 * | --------- | MEM_HEAP_START
 * |     |     |
 * |    \|/    |
 * |           |
 * |    ...    |
 * |           |
 * |    /|\    |
 * |     |     |
 * | --------- | (runtime)
 * | (runtime) | alloc info zone
 * =============
*/

#define MEM_KERNEL_PAGE_START (mb(13))
#define MEM_KERNEL_PAGE_END (MEM_KERNEL_PAGE_START + mb(4))

#define MEM_GFX_MEMORY_START (MEM_KERNEL_PAGE_END)
#define MEM_GFX_MEMORY_END (MEM_GFX_MEMORY_START + mb(16))

#define MEM_START_RESERVED (0x0)
#define MEM_END_RESERVED (MEM_GFX_MEMORY_END)

#define MEM_HEAP_START (MEM_END_RESERVED)

#endif
