/**
 * @file instruction.h
 * @author changfeng (louchangfeng@outlook.com)
 * @brief
 * @version 0.1
 * @date 2021-12-02
 *
 * @copyright Copyright (c) 2021 lcf.
 *
 */

#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_ 1

#include <stdint.h>

#define NUM_INSTRTYPE 30

typedef enum Operator {
  mov_reg_reg, // 0
  mov_reg_mem, // 1
  mov_mem_reg, // 2
  push_reg,    // 3
  pop_reg,     // 4
  call,        // 5
  ret,         // 6
  add_reg_reg, // 7
} op_t;

/**
 * @brief There are 11 addressing modes for operands.
 *
 */
typedef enum OperandType {
  EMPTY,
  IMM,
  REG,
  MM_IMM,
  MM_REG,
  MM_IMM_REG,
  MM_REG1_REG2,
  MM_IMM_REG1_REG2,
  MM_REG2_S,
  MM_IMM_REG2_S,
  MM_REG1_REG2_S,
  MM_IMM_REG1_REG2_S
} od_type_t;

typedef struct Operand {
  od_type_t type;

  int64_t imm;    // immediate number
  int64_t scale;  // scale number
  uint64_t *reg1; // register 1
  uint64_t *reg2; // register 2
} od_t;

typedef struct INST_STRUCT {
  op_t op;  // enums of operators. e.g. mov, call, etc.
  od_t src; // operand src of instruction.
  od_t dst; // operand dst of instruction.
  char code[100];
} inst_t;

// uint64_t decode_od(od_t od);

// handler_t --> a pointer pointing to the function.
typedef void (*handler_t)(uint64_t, uint64_t);

handler_t handler_table[NUM_INSTRTYPE];

/**
 * @brief Initialize the handler table with instruction function handlers
 * match the same function pointer.
 *
 */
void init_handler_table();

/**
 * @brief Iterate through each instruction and execute
 *
 */
void instruction_cycle();

/**
 * @brief Move value in source to the destination
 *
 * dst = src
 *
 * @param src source: register
 * @param dst destination: register
 */
void mov_reg_reg_handler(uint64_t src, uint64_t dst);

/**
 * @brief Move value in source to the destination
 *
 * dst = src
 *
 * @param src source: register
 * @param dst destination: memmory
 */
void mov_reg_mem_handler(uint64_t src, uint64_t dst);
void mov_mem_reg_handler(uint64_t src, uint64_t dst);

/**
 * @brief Add the values in reg1 and reg2 to the `dst`. \n
 *
 * dst = dst + src
 *
 * @param src source: register
 * @param dst destination: register
 */
void add_reg_reg_handler(uint64_t src, uint64_t dst);

/**
 * @brief Call function
 *
 * @param src imm address of called function
 * @param dst empty
 */
void call_handler(uint64_t src, uint64_t dst);

void push_reg_handler(uint64_t src, uint64_t dst);

void pop_reg_handler(uint64_t src, uint64_t dst);

void ret_handler(uint64_t src, uint64_t dst);

#endif // _INSTRUCTION_H_