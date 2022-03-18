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

// Memory Management Unit
#include <assert.h>
#include <common.h>
#include <cpu.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

uint64_t
va2pa(uint64_t vaddr, core_t* cr) {
    return vaddr & (0xffffffffffffffff >> (64 - MAX_INDEX_PHYSICAL_PAGE));
}
