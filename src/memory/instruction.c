#include "memory/instruction.h"
#include "cpu/mmu.h"
#include "cpu/register.h"

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

    return va2pa(v_addr);
  }
}

/**
 * @brief
 *
 */
void instruction_cycle() {
  inst_t *instr = (inst_t *)reg.rip;

  uint64_t src = decode_od(instr->src);
  uint64_t dst = decode_od(instr->dst);

  handler_t handler = handler_table[instr->op];
  handler(src, dst);
}

/**
 * @brief
 *
 */
void init_handler_table() {
  handler_table[add_reg_reg] = &add_reg_reg_handler;
  handler_table[mov_reg_reg] = &mov_reg_reg_handler;
}

void mov_reg_reg_handler(uint64_t src, uint64_t dst) {
  *(uint64_t *)dst = *(uint64_t *)src;
  reg.rip += sizeof(inst_t);
}

/**
 * @brief add the values in reg1 and reg2 to the `dst`.
 *
 * @param src pointer of reg1
 * @param dst pointer of reg2
 */
void add_reg_reg_handler(uint64_t src, uint64_t dst) {
  *(uint64_t *)dst = *(uint64_t *)dst + *(uint64_t *)src;

  // jump to the pointer of next program.
  reg.rip += sizeof(inst_t);
}