/**
 * @file elf.h
 * @author changfeng (louchangfeng@outlook.com)
 * @brief
 * @version 0.1
 * @date 2021-12-03
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef _ELF_H_
#define _ELF_H_ 1

#include <stdint.h>

#include "memory/instruction.h"

#define INST_LEN 15

inst_t program[INST_LEN];

#endif // _ELF_H_