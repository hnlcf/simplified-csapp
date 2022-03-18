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
#ifndef CSAPP_CPU_H
#define CSAPP_CPU_H
#include <stdint.h>
#include <stdlib.h>

/*======================================*/
/*      registers                       */
/*======================================*/

// struct of registers in each core
// resource accessible to the core itself only

typedef struct REGISTER_STRUCT {
    // return value
    union {
        uint64_t rax;
        uint32_t eax;
        uint16_t ax;
        struct {
            uint8_t al;
            uint8_t ah;
        };
    };

    // callee saved
    union {
        uint64_t rbx;
        uint32_t ebx;
        uint16_t bx;
        struct {
            uint8_t bl;
            uint8_t bh;
        };
    };

    // 4th argument
    union {
        uint64_t rcx;
        uint32_t ecx;
        uint16_t cx;
        struct {
            uint8_t cl;
            uint8_t ch;
        };
    };
    // 3th argument
    union {
        uint64_t rdx;
        uint32_t edx;
        uint16_t dx;
        struct {
            uint8_t dl;
            uint8_t dh;
        };
    };
    // 2nd argument
    union {
        uint64_t rsi;
        uint32_t esi;
        uint16_t si;
        struct {
            uint8_t sil;
            uint8_t sih;
        };
    };
    // 1st argument
    union {
        uint64_t rdi;
        uint32_t edi;
        uint16_t di;
        struct {
            uint8_t dil;
            uint8_t dih;
        };
    };

    // callee saved frame pointer
    union {
        uint64_t rbp;
        uint32_t ebp;
        uint16_t bp;
        struct {
            uint8_t bpl;
            uint8_t bph;
        };
    };
    // stack pointer
    union {
        uint64_t rsp;
        uint32_t esp;
        uint16_t sp;
        struct {
            uint8_t spl;
            uint8_t sph;
        };
    };

    // 5th argument
    union {
        uint64_t r8;
        uint32_t r8d;
        uint16_t r8w;
        uint8_t  r8b;
    };
    // 6th argument
    union {
        uint64_t r9;
        uint32_t r9d;
        uint16_t r9w;
        uint8_t  r9b;
    };

    // caller saved
    union {
        uint64_t r10;
        uint32_t r10d;
        uint16_t r10w;
        uint8_t  r10b;
    };
    // caller saved
    union {
        uint64_t r11;
        uint32_t r11d;
        uint16_t r11w;
        uint8_t  r11b;
    };

    // callee saved
    union {
        uint64_t r12;
        uint32_t r12d;
        uint16_t r12w;
        uint8_t  r12b;
    };
    // callee saved
    union {
        uint64_t r13;
        uint32_t r13d;
        uint16_t r13w;
        uint8_t  r13b;
    };
    // callee saved
    union {
        uint64_t r14;
        uint32_t r14d;
        uint16_t r14w;
        uint8_t  r14b;
    };
    // callee saved
    union {
        uint64_t r15;
        uint32_t r15d;
        uint16_t r15w;
        uint8_t  r15b;
    };
} reg_t;

/*======================================*/
/*      sram cache                      */
/*======================================*/

/*
The components of a SRAM cache address:
Note: SRAM cache address is the translated physical address
|   TAG_LEN     |   INDEX_LEN   |   OFFSET_LEN  |
+---------------+---------------+---------------+
|   tag         |   index       |   offset      |
+---------------+---------------+---------------+
|   ADDR_LEN                                    |
*/

/*======================================*/
/*      cpu core                        */
/*======================================*/

typedef struct CPU_FLAGS_STRUCT {
    union {
        uint64_t __cpu_flag_values;
        struct {
            uint16_t CF;  // carry flag: detect overflow for unsigned operations
            uint16_t ZF;  // zero flag: result is zero
            uint16_t SF;  // sign flag: result is negative: highest bit
            uint16_t
                OF;  // overflow flag: detect overflow for signed operations
        };
    };

} cpu_flag_t;

typedef struct CORE_STRUCT {
    // program counter or instruction pointer
    union {
        uint64_t rip;
        uint32_t eip;
    };

    // condition code flags of most recent (latest) operation
    // condition codes will only be set by the following integer arithmetic
    // instructions

    /* integer arithmetic instructions
        inc     increment 1
        dec     decrement 1
        neg     negate
        not     complement
        ----------------------------
        add     add
        sub     subtract
        imul    multiply
        xor     exclusive or
        or      or
        and     and
        ----------------------------
        sal     left shift
        shl     left shift (same as sal)
        sar     arithmetic right shift
        shr     logical right shift
    */

    /* comparison and test instructions
        cmp     compare
        test    test
    */

    // flags
    cpu_flag_t flags;

    // register files
    reg_t reg;
} core_t;

#define NUM_CORES 1  // define cpu core array to support core level parallelism1
extern core_t
    cores[NUM_CORES];  // global cpu core, cores --> `core_t cores[NUM_CORES]`.
extern uint64_t ACTIVE_CORE;  // active core for current task

/*======================================*/
/*      instruction set architecture    */
/*======================================*/

// data structures
typedef enum INST_OPERATOR {
    INST_MOV,    // 0
    INST_PUSH,   // 1
    INST_POP,    // 2
    INST_LEAVE,  // 3
    INST_CALL,   // 4
    INST_RET,    // 5
    INST_ADD,    // 6
    INST_SUB,    // 7
    INST_CMP,    // 8
    INST_JNE,    // 9
    INST_JMP,    // 10
} inst_op_e;

typedef enum OPERAND_TYPE {
    EMPTY,                  // 0
    IMM,                    // 1
    REG,                    // 2
    MEM_IMM,                // 3
    MEM_REG1,               // 4
    MEM_IMM_REG1,           // 5
    MEM_REG1_REG2,          // 6
    MEM_IMM_REG1_REG2,      // 7
    MEM_REG2_SCAL,          // 8
    MEM_IMM_REG2_SCAL,      // 9
    MEM_REG1_REG2_SCAL,     // 10
    MEM_IMM_REG1_REG2_SCAL  // 11
} od_type_e;

typedef struct OPERAND_STRUCT {
    od_type_e type;  // IMM, REG, MEM
    uint64_t  imm;   // immediate number
    uint64_t  scal;  // scale number to register 2
    uint64_t  reg1;  // main register
    uint64_t  reg2;  // register 2
} od_t;

// local variables are allocated in stack in run-time
// we don't consider local STATIC variables
// ref: Computer Systems: A Programmer's Perspective 3rd
// Chapter 7 Linking: 7.5 Symbols and Symbol Tables
typedef struct INST_STRUCT {
    inst_op_e op;   // enum of operators. e.g. mov, call, etc.
    od_t      src;  // operand src of instruction
    od_t      dst;  // operand dst of instruction
} inst_t;

#define MAX_INSTRUCTION_CHAR 64
#define NUM_INSTRTYPE        14

// CPU's instruction cycle: execution of instructions
void instruction_cycle(core_t* cr);

/*--------------------------------------*/
// place the functions here because they requires the core_t type

/*--------------------------------------*/
// mmu functions

// translate the virtual address to physical address in MMU
// each MMU is owned by each core
uint64_t va2pa(uint64_t vaddr, core_t* cr);

// symbols from isa and sram
void print_register(core_t* cr);
void print_stack(core_t* cr);

// end of include guard
#endif  // CSAPP_CPU_H
