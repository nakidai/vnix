#ifndef _vnix_tss_h
#define _vnix_tss_h

#include <stdint.h>

#include <vnix/kerneldef.h>

struct tss_addr {
	uint32_t limit;
	uint32_t base;
};

extern struct tss_addr tss_addr;

void tss_init(void);

#endif
