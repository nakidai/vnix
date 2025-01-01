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
	FILE  : sys/vmm_owned.c

	owned virtual memory managament
*/

#include <stdint.h>
#include <stdbool.h>

#include <vnix/vmm_owned.h>
#include <vnix/vmm.h>
#include <vnix/mem_table.h>
#include <vnix/panic.h>

#include <libk/kstdmem.h>

struct region {
	uint32_t start;
	uint32_t end;
};

struct owner {
	bool is_active;
	struct vmm_dir_entry* dir;
};

static struct owner owners[VMM_OWNED_MAX_OWNERS];
static vmm_owned_oid_t crnt_owner = 0;

void vmm_owned_init(void)
{
	vmm_owned_add_owner(0, (struct vmm_dir_entry*) MEM_KERNEL_PAGE_START);
}

void vmm_owned_add_owner(vmm_owned_oid_t oid, struct vmm_dir_entry* dir)
{
	if (oid > VMM_OWNED_MAX_OWNERS)
		panic("Can't create owner, invalid oid.\n");

	struct owner* owner = &owners[oid];
	owner->is_active    = true;
	owner->dir          = dir;
}

void vmm_owned_rem_owner(vmm_owned_oid_t oid)
{
	if (oid > VMM_OWNED_MAX_OWNERS || !owners[oid].is_active)
		panic("Can't remove owner, invalid oid.\n");

	struct owner* owner = &owner[oid];
	owner->is_active    = false;
}

void vmm_owned_switch(vmm_owned_oid_t oid)
{
	if (oid > VMM_OWNED_MAX_OWNERS || !owners[oid].is_active)
		panic("Can't switch owner, invalid oid.\n");

	crnt_owner = oid;
	vmm_set_vmm_context(owners[oid].dir);
}

static bool check_other_owner(uint32_t page);

bool vmm_owned_map(uint32_t page, struct vmm_dir_entry* entry)
{
	if (check_other_owner(page))
		return false;

	struct owner* owner = &owners[crnt_owner];
	owner->dir[page]    = *entry;

	return true;
}

bool vmm_owned_munmap(uint32_t page)
{
	if (check_other_owner(page))
		return false;

	struct owner* owner         = &owners[crnt_owner];
	struct vmm_dir_entry* entry = &owner->dir[page];

	kmemset(entry, 0, sizeof(struct vmm_dir_entry));
	entry->addr    = vmm_get_addr_by_page(page);
	entry->present = true;

	return true;
}

static bool check_other_owner_by_owner(uint32_t page, struct owner* owner);

static bool check_other_owner(uint32_t page)
{
	for (int i = 0; i < VMM_OWNED_MAX_OWNERS; i++) {
		struct owner* owner = &owners[i];

		if (!owner->is_active || i == crnt_owner)
			continue;

		if (check_other_owner_by_owner(page, owner))
			return true;
	}

	return false;
}

static bool check_other_owner_by_owner(uint32_t page, struct owner* owner)
{
	for (int i = 0; i < VMM_PAGE_DIR_ENTRY_COUNT; i++) {
		struct vmm_dir_entry* entry = &owner->dir[i];

		if (!(entry->accessed == 0 &&
				entry->addr == vmm_get_addr_by_page(i) &&
				entry->avalidable0 == 0 &&
				entry->avalidable1 == 0 &&
				entry->pcd == 0 &&
				entry->pwt == 0 &&
				entry->read_write == 0 &&
				entry->user_supervisor == 0))
			return true;
	}

	return false;
}
