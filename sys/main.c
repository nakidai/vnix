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
	FILE  : sys/main.c

	main kernel file
*/

#include <vnix/multiboot.h>
#include <vnix/halt.h>
#include <vnix/interrput.h>
#include <vnix/mem_table.h>
#include <vnix/kio.h>
#include <vnix/heap.h>
#include <vnix/fs.h>
#include <vnix/panic.h>
#include <vnix/devfs.h>
#include <vnix/dev_console.h>
#include <vnix/faluts.h>
#include <vnix/port_io.h>

void kernel_entry(struct multiboot* args)
{
	kputs("Processor errors initing...");
	falut_setup_faluts();
	kok();

	kputs("Heap initing...");
	heap_init(kb(args->mem_upper));
	kok();

	kputs("Fs initing...");
	fs_init();
	kok();

	kputs("Creating /dev/...");
	if (!fs_mkdir(fs_get_root(), "dev", 0))
		panic("Can't create /dev/ directory!\n");
	kok();

	kputs("Devfs initing...");
	devfs_init();
	kok();

	dev_console_init();

	kputs("Kernel build at " __DATE__ " " __TIME__ ".\n");

	halt();
}
