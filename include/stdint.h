#ifndef _stdint_h
#define _stdint_h

typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long int64_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

typedef int8_t int8_least_t;
typedef int16_t int16_least_t; 
typedef int32_t int32_least_t;
typedef int64_t int64_least_t;
typedef uint8_t uint8_least_t;
typedef uint16_t uint16_least_t;
typedef uint32_t uint32_least_t;
typedef uint64_t uint64_least_t;

typedef int8_t int8_fast_t; 
typedef int16_t int16_fast_t; 
typedef int32_t int32_fast_t;
typedef int64_t int64_fast_t;
typedef uint8_t uint8_fast_t;
typedef uint16_t uint16_fast_t;
typedef uint32_t uint32_fast_t;
typedef uint64_t uint64_fast_t;

typedef int32_t intptr_t;
typedef uint32_t uintptr_t;

typedef int64_t intmax_t;
typedef uint64_t uintmax_t;

#endif
