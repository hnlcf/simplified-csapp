/**
 * @file mmu.h
 * @author changfeng (louchangfeng@outlook.com)
 * @brief memory management unit
 * @version 0.1
 * @date 2021-12-03
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef _MMU_H_
#define _MMU_H_ 1

#include <stdint.h>

/**
 * @brief Convertion of virtual address --> physical address
 *
 * @param v_addr the virtual address
 * @return `uint64_t` - phgysical address
 */
uint64_t va2pa(uint64_t v_addr);

#endif // _MMU_H_