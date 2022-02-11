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

#include "common.h"
#include "cpu.h"
#include "memory.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM_INSTRUCTION_CYCLE 100

static void
TestAddFunctionCallAndComputation();

int
main()
{
  printf("hello world\n");
  TestAddFunctionCallAndComputation();
  return 0;
}

static void
TestAddFunctionCallAndComputation()
{
  uint64_t ACTIVE_CORE;
  ACTIVE_CORE = 0x0;
  core_t* cores;
  cores = (core_t*)malloc(sizeof(core_t) * NUM_CORES);

  core_t* ac = (core_t*)&cores[ACTIVE_CORE];

  // init state
  ac->reg.rax = 0xabcd;
  ac->reg.rbx = 0x8000670;
  ac->reg.rcx = 0x8000670;
  ac->reg.rdx = 0x12340000;
  ac->reg.rsi = 0x7ffffffee208;
  ac->reg.rdi = 0x1;
  ac->reg.rbp = 0x7ffffffee110;
  ac->reg.rsp = 0x7ffffffee0f0;

  ac->flags.__cpu_flag_values = 0;

  write64bits_dram(va2pa(0x7ffffffee110, ac), 0x0000000000000000, ac); // rbp
  write64bits_dram(va2pa(0x7ffffffee108, ac), 0x0000000000000000, ac);
  write64bits_dram(va2pa(0x7ffffffee100, ac), 0x0000000012340000, ac);
  write64bits_dram(va2pa(0x7ffffffee0f8, ac), 0x000000000000abcd, ac);
  write64bits_dram(va2pa(0x7ffffffee0f0, ac), 0x0000000000000000, ac); // rsp

  // 2 before call
  // 3 after call before push
  // 5 after rbp
  // 13 before pop
  // 14 after pop before ret
  // 15 after ret
  char assembly[15][MAX_INSTRUCTION_CHAR] = {
    "push   %rbp",             // 0
    "mov    %rsp,%rbp",        // 1
    "mov    %rdi,-0x18(%rbp)", // 2
    "mov    %rsi,-0x20(%rbp)", // 3
    "mov    -0x18(%rbp),%rdx", // 4
    "mov    -0x20(%rbp),%rax", // 5
    "add    %rdx,%rax",        // 6
    "mov    %rax,-0x8(%rbp)",  // 7
    "mov    -0x8(%rbp),%rax",  // 8
    "pop    %rbp",             // 9
    "retq",                    // 10
    "mov    %rdx,%rsi",        // 11
    "mov    %rax,%rdi",        // 12
    "callq  0",                // 13
    "mov    %rax,-0x8(%rbp)",  // 14
  };
  ac->rip = (uint64_t)&assembly[11];
  sprintf(assembly[13], "callq  $%p", &assembly[0]);

  printf("begin\n");
  int time = 0;
  while (time < 15) {
    instruction_cycle(ac);
    print_register(ac);
    print_stack(ac);
    time++;
  }

  // gdb state ret from func
  int match = 1;
  match = match && ac->reg.rax == 0x1234abcd;
  match = match && ac->reg.rbx == 0x8000670;
  match = match && ac->reg.rcx == 0x8000670;
  match = match && ac->reg.rdx == 0xabcd;
  match = match && ac->reg.rsi == 0x12340000;
  match = match && ac->reg.rdi == 0xabcd;
  match = match && ac->reg.rbp == 0x7ffffffee110;
  match = match && ac->reg.rsp == 0x7ffffffee0f0;

  if (match) {
    printf("register match\n");
  } else {
    printf("register mismatch\n");
  }

  match = match && (read64bits_dram(va2pa(0x7ffffffee110, ac), ac) ==
                    0x0000000000000000); // rbp
  match = match && (read64bits_dram(va2pa(0x7ffffffee108, ac), ac) ==
                    0x000000001234abcd);
  match = match && (read64bits_dram(va2pa(0x7ffffffee100, ac), ac) ==
                    0x0000000012340000);
  match = match && (read64bits_dram(va2pa(0x7ffffffee0f8, ac), ac) ==
                    0x000000000000abcd);
  match = match && (read64bits_dram(va2pa(0x7ffffffee0f0, ac), ac) ==
                    0x0000000000000000); // rsp

  if (match) {
    printf("memory match\n");
  } else {
    printf("memory mismatch\n");
  }

  free(cores);
}
