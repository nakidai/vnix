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
	FILE  : sys/arch/x86/idt.c

	work with Interrput Descriptor Table
*/

#include <stdint.h>

#include <libk/kstdmem.h>

#include <arch/idt.h>
#include <arch/asm.h>

#include <vnix/kerneldef.h>

#define IDT_MAX_ENTRIES 256

struct idt_ptr {
	uint32_t limit;
	uint32_t base;
} attr_packed;

struct idt_entry {
	uint16_t base_low;
	uint16_t sel;
	uint8_t zero;
	uint8_t flags;
	uint16_t base_high;
} attr_packed;

static struct idt_ptr idt_ptr;
static struct idt_entry idt_entries[IDT_MAX_ENTRIES];

static void set_entry(uint8_t i, uint32_t base, uint16_t sel, uint8_t flags);

extern void idt_flush(uint32_t);

extern void isr8();
extern void isr13();
extern void isr14();

void idt_init(void)
{
	idt_ptr.limit = sizeof(struct idt_entry) * IDT_MAX_ENTRIES - 1;
	idt_ptr.base  = (uint32_t) (uint64_t) &idt_entries;

	kmemset(&idt_entries, 0, sizeof(struct idt_entry) * IDT_MAX_ENTRIES);

	outb(0x20, 0x11);
	outb(0xA0, 0x11);
	outb(0x21, 0x20);
	outb(0xA1, 0x28);
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	outb(0x21, 0x0);
	outb(0xA1, 0x0);

	set_entry(8, (uint32_t) (uint64_t) isr8, 0x08, 0x8e);
	set_entry(13, (uint32_t) (uint64_t) isr13, 0x08, 0x8e);
	set_entry(14, (uint32_t) (uint64_t) isr14, 0x08, 0x0e);

	idt_flush((uint32_t) (uint64_t) &idt_entries);
}

static void set_entry(uint8_t i, uint32_t base, uint16_t sel, uint8_t flags)
{
	struct idt_entry* entry = &idt_entries[i];

	entry->base_low  = base & 0xffff;
	entry->base_high = (base >> 16) & 0xffff;

	entry->sel   = sel;
	entry->zero  = 0;
	entry->flags = flags | 0x60;
}