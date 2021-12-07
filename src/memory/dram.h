/**
 * @file dram.h
 * @author changfeng (louchangfeng@outlook.com)
 * @brief
 * @version 0.1
 * @date 2021-12-03
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef _DRAM_H_
#define _DRAM_H_ 1

#include <stdint.h>

#define MM_LEN 1000

uint8_t mm[MM_LEN]; // physical memory

uint64_t read64bits_dram(uint64_t p_addr);
void write64bits_dram(uint64_t p_addr, uint64_t data);

void print_register();
void print_stack();

#endif // _DRAM_H_