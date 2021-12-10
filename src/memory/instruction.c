#include "memory/instruction.h"
#include "cpu/mmu.h"
#include "cpu/register.h"
#include "memory/dram.h"

#include <stdio.h>

// TODO: the return of decode_od() is confusing.

/***************************************************************
 * @brief decode for operand. \n
 *
 * imm --> immediate number
 * reg --> pointer of register
 * mm --> physical address
 *
 * @param od the operand of instruction
 * @return uint64_t
 **************************************************************/
static uint64_t decode_od(od_t od) {
  if (od.type == IMM) {
    return *((uint64_t *)&od.imm);
  } else if (od.type == REG) {
    return (uint64_t)od.reg1;
  } else {
    uint64_t v_addr = 0;

    if (od.type == MM_IMM) {
      v_addr = od.imm;
    } else if (od.type == MM_REG) {
      v_addr = *(od.reg1);
    } else if (od.type == MM_IMM_REG) {
      v_addr = od.imm + *(od.reg1);
    } else if (od.type == MM_REG1_REG2) {
      v_addr = *(od.reg1) + *(od.reg2);
    } else if (od.type == MM_IMM_REG1_REG2) {
      v_addr = od.imm + *(od.reg1) + *(od.reg2);
    } else if (od.type == MM_REG2_S) {
      v_addr = (*(od.reg2)) * od.scale;
    } else if (od.type == MM_IMM_REG2_S) {
      v_addr = od.imm + (*(od.reg2)) * od.scale;
    } else if (od.type == MM_REG1_REG2_S) {
      v_addr = *(od.reg1) + (*(od.reg2)) * od.scale;
    } else if (od.type == MM_IMM_REG1_REG2_S) {
      v_addr = od.imm + *(od.reg1) + (*(od.reg2)) * od.scale;
    }

    return v_addr;
  }
}

/**
 * @brief Iterate through each instruction and execute
 *
 */
void instruction_cycle() {
  inst_t *instr = (inst_t *)reg.rip;

  // acquire instruction params
  uint64_t src = decode_od(instr->src);
  uint64_t dst = decode_od(instr->dst);

  // execute instuction
  handler_t handler = handler_table[instr->op];
  handler(src, dst);

  // display instruction
  printf("\t%s\n", instr->code);
}

/**
 * @brief Initialize the handler table with instruction function handlers
 * match the same function pointer.
 *
 */
void init_handler_table() {
  handler_table[mov_reg_reg] = &mov_reg_reg_handler;
  handler_table[mov_reg_mem] = &mov_reg_mem_handler;
  handler_table[mov_mem_reg] = &mov_mem_reg_handler;
  handler_table[add_reg_reg] = &add_reg_reg_handler;
  handler_table[push_reg] = &push_reg_handler;
  handler_table[pop_reg] = &pop_reg_handler;
  handler_table[call] = &call_handler;
  handler_table[ret] = &ret_handler;
}

/**
 * @brief Move value in source to the destination
 *
 * dst = src
 *
 * @param src source
 * @param dst destination
 */
void mov_reg_reg_handler(uint64_t src, uint64_t dst) {
  *(uint64_t *)dst = *(uint64_t *)src;

  // jump to the pointer of next program.
  reg.rip += sizeof(inst_t);
}

void mov_reg_mem_handler(uint64_t src, uint64_t dst) {
  write64bits_dram(va2pa(dst), *(uint64_t *)src);

  // jump to the pointer of next program.
  reg.rip += sizeof(inst_t);
}

void mov_mem_reg_handler(uint64_t src, uint64_t dst) {
  *(uint64_t *)dst = read64bits_dram(va2pa(src));

  // jump to the pointer of next program.
  reg.rip += sizeof(inst_t);
}

/**
 * @brief Add the values in reg1 and reg2 to the `dst`. \n
 *
 * dst = dst + src
 *
 * @param src pointer of reg1
 * @param dst pointer of reg2
 */
void add_reg_reg_handler(uint64_t src, uint64_t dst) {
  // TODO: rewrite with recursive

  *(uint64_t *)dst = *(uint64_t *)dst + *(uint64_t *)src;

  // jump to the pointer of next program.
  reg.rip += sizeof(inst_t);
}

void push_reg_handler(uint64_t src, uint64_t dst) {
  reg.rsp -= 0x8;
  write64bits_dram(va2pa(reg.rsp), *(uint64_t *)src);

  reg.rip += sizeof(inst_t);
}

void pop_reg_handler(uint64_t src, uint64_t dst) {
  *(uint64_t *)src = read64bits_dram(va2pa(reg.rsp));

  reg.rsp += 0x8;
  reg.rip += sizeof(inst_t);
}

void call_handler(uint64_t src, uint64_t dst) {
  // leave 8-byte stack space out
  reg.rsp -= 0x8;
  // write the return address to rsp --> push return address onto stack
  write64bits_dram(va2pa(reg.rsp), reg.rip + sizeof(inst_t));

  // function address --> PC(program counter)
  // PC --> jump to run called function
  reg.rip = src;
}

void ret_handler(uint64_t src, uint64_t dst) {
  reg.rip = read64bits_dram(va2pa(reg.rsp));

  reg.rsp += 0x8;
}
