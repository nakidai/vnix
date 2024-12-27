#include <stdint.h>
#include <stddef.h>

#include <arch/gdt.h>
#include <arch/tss.h>

#include <vnix/kerneldef.h>

#define GDT_ENTRY_COUNT 6

struct gdt_entry {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
} attr_packed;

struct gdt_ptr {
	uint32_t limit;
	uint32_t base;
} attr_packed;

static struct gdt_ptr gdt_ptr;
static struct gdt_entry gdt_entries[GDT_ENTRY_COUNT];

static void set_entry(size_t i, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity);

extern void gdt_flush(uint32_t);
extern void tss_flush(void);

void gdt_init(void)
{
	gdt_ptr.limit = (sizeof(struct gdt_entry) * (GDT_ENTRY_COUNT + 1)) - 1;
	gdt_ptr.base = (uint32_t) (uint64_t) &gdt_entries;

	set_entry(0, 0, 0, 0, 0);

	set_entry(1, 0, 0xffffffff, 0x9a, 0xcf);
	set_entry(2, 0, 0xffffffff, 0x92, 0xcf);

	set_entry(3, 0, 0xffffffff, 0xfa, 0xcf);
	set_entry(4, 0, 0xffffffff, 0xf2, 0xcf);

	set_entry(5, tss_addr.base, tss_addr.limit, 0xe9, 0x00);
	set_entry(6, 0, 0xffffffff, 0x80, 0xcf);

	gdt_flush((uint32_t) (uint64_t) &gdt_ptr);
	tss_flush();
}

static void set_entry(size_t i, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity)
{
	struct gdt_entry* entry = &gdt_entries[i];

	entry->base_low    = (base & 0xffff);
	entry->base_middle = (base >> 16) & 0xff;
	entry->base_high   = (base >> 24) & 0xff;

	entry->limit_low   = (limit & 0xffff);
	entry->granularity = ((limit >> 16) & 0x0f) | (granularity & 0xf0);
	entry->access      = access;
}
