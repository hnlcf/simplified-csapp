/* CSAPP - Introduction to Computer Systems.
 * Author:      louchangfeng@outlook.com
 * Github:      https://github.com/hnlcf/simplified-csapp
 *
 * This project is exclusively owned by louchangfeng
 * and shall not be used for commercial and profitting purpose
 * without louchangfeng's permission.
 *
 * Thanks for yangminz's code repository and videos in my learning.
 */

#pragma once
// include guards to prevent double declaration of any identifiers
// such as types, enums and static variables
#ifndef CSAPP_COMMON_H
#define CSAPP_COMMON_H
#include <stdint.h>

/*======================================*/
/**/
/*======================================*/
#define DEBUG_INSTRUCTIONCYCLE 0x1
#define DEBUG_REGISTERS        0x2
#define DEBUG_PRINTSTACK       0x4
#define DEBUG_PRINTCACHESET    0x8
#define DEBUG_CACHEDETAILS     0x10
#define DEBUG_MMU              0x20
#define DEBUG_LINKER           0x40
#define DEBUG_LOADER           0x80
#define DEBUG_PARSEINST        0x100

#define DEBUG_VERBOSE_SET 0x1

// do page walk
#define DEBUG_ENABLE_PAGE_WALK 0

// use sram cache for memory access
#define DEBUG_ENABLE_SRAM_CACHE 0

// printf wrapper
uint64_t debug_printf(uint64_t open_set, const char* format, ...);

// type converter
// uint32 to its equivalent float with rounding
uint32_t uint2float(uint32_t u);

// convert string dec or hex to the integer bitmap
uint64_t string2uint(const char* str);
uint64_t string2uint_range(const char* str, int start, int end);

#endif  // CSAPP_COMMON_H