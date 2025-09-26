#ifndef TYPES_H
#define TYPES_H


typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;
typedef unsigned int size_t;

typedef char s8;
typedef short s16;
typedef int s32;
typedef long long s64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef float f32;
typedef double f64;

typedef s32 intptr_t;
typedef u32 uintptr_t;
typedef s32 ptrdiff_t;

// Old code insists on treating strlen's return type as a signed integer
typedef s32 strlen_t;

typedef s32 ssize_t;


#endif
