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
	DATE  : 1.1.2025
	FILE  : sys/main.c

	main kernel file
*/

#include <vnix/multiboot.h>
#include <vnix/halt.h>
#include <vnix/interrput.h>
#include <vnix/vmm.h>
#include <vnix/mem_table.h>
#include <vnix/kio.h>
#include <vnix/heap.h>
#include <vnix/fs.h>
#include <vnix/vmm_owned.h>

void kernel_entry(struct multiboot* args)
{
	kputs("Kernel build at " __DATE__ " " __TIME__ ".\n");

	kputs("Initing owned vmm...");
	vmm_owned_init();
	kok();

	kputs("Initing heap...");
	heap_init(vmm_get_page_by_addr(args->mem_upper * 1024) - 1);
	kok();

	kputs("Initing fs...");
	fs_init();

	halt();
}
