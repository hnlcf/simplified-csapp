/**
 * @file register.h
 * @author changfeng (louchangfeng@outlook.com)
 * @brief describe the basic structure of register.
 * @version 0.1
 * @date 2021-12-01
 *
 * @copyright Copyright (c) 2021 lcf.
 *
 */

#ifndef _REGISTER_H_
#define _REGISTER_H_ 1

#include <stdint.h>

/**
 * @brief The register structure of CPU.
 *
 */
typedef struct REG_STRUCT {
  /* rax-->return value, accumulate */
  union {
    struct {
      uint8_t al;
      uint8_t ah;
    };
    uint16_t ax;
    uint32_t eax;
    uint64_t rax;
  };

  /* rbx-->saved by caller, base */
  union {
    struct {
      uint8_t bl;
      uint8_t bh;
    };
    uint16_t bx;
    uint32_t ebx;
    uint64_t rbx;
  };

  /* rcx-->the fourth arg, counter */
  union {
    struct {
      uint8_t cl;
      uint8_t ch;
    };
    uint16_t cx;
    uint32_t ecx;
    uint64_t rcx;
  };

  /* rdx-->the third arg, data */
  union {
    struct {
      uint8_t dl;
      uint8_t dh;
    };
    uint16_t dx;
    uint32_t edx;
    uint64_t rdx;
  };

  /* rsi-->the second arg, source indes */
  union {
    uint16_t si;
    uint32_t esi;
    uint64_t rsi;
  };

  /* rdi-->the first arg, destination index */
  union {
    uint16_t di;
    uint32_t edi;
    uint64_t rdi;
  };

  /* rbp-->base pointer, save by caller */
  union {
    uint16_t bp;
    uint32_t ebp;
    uint64_t rbp;
  };

  /* rsp-->stack pointer */
  union {
    uint16_t sp;
    uint32_t esp;
    uint64_t rsp;
  };

  uint64_t rip;           // program counter--PC or instruction pointer
  uint8_t CF, SF, ZF, OF; // condition code flags
} reg_t;

/**
 * @brief define a global register.
 *
 */
reg_t reg;

#endif // _REGISTER_H_
