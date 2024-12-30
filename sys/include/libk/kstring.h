#ifndef _libk_kstring_h
#define _libk_kstring_h

#include <stdbool.h>
#include <stddef.h>

size_t kstrlen(const char* str);
void kstrcpy(char* dest, const char* src);
bool kstrcmp(const char* str0, const char* str1);

#endif
