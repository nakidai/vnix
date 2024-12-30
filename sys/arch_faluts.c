#include <vnix/arch_faluts.h>
#include <vnix/halt.h>
#include <vnix/vga.h>

void falut_double_falut(void* _)
{
	vga_put("Double falut!");
	halt();
}

void falut_general_protection_falut(void* _)
{
	halt();
}

void falut_page_falut(void* _)
{
	halt();
}
