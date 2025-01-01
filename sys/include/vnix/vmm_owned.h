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
	FILE  : sys/include/vnix/vmm_owned.h

	owned virtual memory managament
*/

#ifndef _vmm_owned_h
#define _vmm_owned_h

#include <stdint.h>
#include <stdbool.h>

#include <vnix/vmm.h>

#define VMM_OWNED_MAX_OWNERS 512

typedef uint32_t vmm_owned_oid_t; // owner id

void vmm_owned_init(void);

void vmm_owned_add_owner(vmm_owned_oid_t oid, struct vmm_dir_entry* dir);
void vmm_owned_rem_owner(vmm_owned_oid_t oid);

void vmm_owned_switch(vmm_owned_oid_t oid);

bool vmm_owned_map(uint32_t page, struct vmm_dir_entry* entry);
bool vmm_owned_munmap(uint32_t page);

#endif
