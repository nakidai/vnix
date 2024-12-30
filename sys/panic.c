#include <vnix/panic.h>
#include <vnix/kio.h>
#include <vnix/halt.h>

void panic(const char* msg)
{
	kputs("Kernel paniced: ");
	kputs(msg);

	halt();
}
