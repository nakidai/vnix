#ifndef _cpu_flags_h
#define _cpu_flags_h

#include <vnix/kerneldef.h>

struct cr0_flags {
	unsigned int pe : 1;
	unsigned int mp : 1;
	unsigned int em : 1;
	unsigned int ts : 1;
	unsigned int et : 1;
	unsigned int ne : 1;

	unsigned int _unused0 : 11;

	unsigned int wp : 1;
	
	unsigned int _unused1 : 2;

	unsigned int am : 1;

	unsigned int _unused2 : 11;

	unsigned int nw : 1;
	unsigned int cd : 1;
	unsigned int pg : 1;

	unsigned int _unused3 : 1;
} attr_packed;

struct cr0_flags get_cr0_flags(void);
void set_cr0_flags(struct cr0_flags flags);

#endif
