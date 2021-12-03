#include "cpu/mmu.h"
#include "cpu/register.h"
#include "disk/elf.h"
#include "memory/dram.h"
#include "memory/instruction.h"

#include <stdio.h>

int main() {
  init_handler_table();

  // init register
  reg.rax = 0x12340000;
  reg.rbx = 0x0;
  reg.rcx = 0x8000660;
  reg.rbx = 0xabcd;
  reg.rsi = 0x7ffffffee2f8;
  reg.rdi = 0x1;
  reg.rbp = 0x7ffffffee210;
  reg.rsp = 0x7ffffffee1f0;

  reg.rip = (uint64_t)&program[11];

  mm[va2pa(0x7ffffffee210)] = (uint8_t)0x08000660; // rbp
  mm[va2pa(0x7ffffffee208)] = (uint8_t)0x0;
  mm[va2pa(0x7ffffffee200)] = (uint8_t)0xabcd;
  mm[va2pa(0x7ffffffee1f8)] = (uint8_t)0x12340000;
  mm[va2pa(0x7ffffffee1f0)] = (uint8_t)0x08000660; // rsp

  // run instruction
  for (int i = 0; i < 15; i++) {
    instruction_cycle();
  }

  // verify
  int match = 1;

  match = match && (reg.rax == 0x1234abcd);
  match = match && (reg.rbx == 0x0);
  match = match && (reg.rcx == 0x8000660);
  match = match && (reg.rbx == 0x12340000);
  match = match && (reg.rsi == 0xabcd);
  match = match && (reg.rdi == 0x12340000);
  match = match && (reg.rbp == 0x7ffffffee210);
  match = match && (reg.rsp == 0x7ffffffee1f0);

  if (match == 1) {
    printf("register match\n");
  } else {
    printf("register not match\n");
  }

  match = match && (mm[va2pa(0x7ffffffee210)] == 0x08000660); // rbp
  match = match && (mm[va2pa(0x7ffffffee208)] == 0x1234abcd);
  match = match && (mm[va2pa(0x7ffffffee200)] == 0xabcd);
  match = match && (mm[va2pa(0x7ffffffee1f8)] == 0x12340000);
  match = match && (mm[va2pa(0x7ffffffee1f0)] == 0x08000660); // rsp

  if (match == 1) {
    printf("memory match\n");
  } else {
    printf("memory not match\n");
  }

  return 0;
}
