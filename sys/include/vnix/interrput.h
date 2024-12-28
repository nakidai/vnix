#ifndef _vnix_interrput_h
#define _vnix_interrput_h

#include <stddef.h>

typedef void (*interrput_handler_f)(void*);

void interrput_set(size_t i, interrput_handler_f handler);

#endif
