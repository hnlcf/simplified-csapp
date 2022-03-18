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
#ifndef CSAPP_MEMORY_H
#define CSAPP_MEMORY_H

#include <cpu.h>
#include <stdint.h>

/*======================================*/
/*      physical memory on dram chips   */
/*======================================*/

// physical memory space is decided by the physical address
// in this simulator, there are 4 + 6 + 6 = 16 bit physical adderss
// then the physical space is (1 << 16) = 65536
// total 16 physical memory
#define PHYSICAL_MEMORY_SPACE   65536
#define MAX_INDEX_PHYSICAL_PAGE 15

// physical memory
// 16 physical memory pages
extern uint8_t pm[PHYSICAL_MEMORY_SPACE];

/*======================================*/
/*             memory R/W               */
/*======================================*/

// used by instructions: read or write uint64_t to DRAM
uint64_t read64bits_dram(uint64_t paddr, core_t* cr);
void     write64bits_dram(uint64_t paddr, uint64_t data, core_t* cr);

#endif  // CSAPP_MEMORY_H
