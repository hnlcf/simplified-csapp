#include "memory/dram.h"
#include "cpu/mmu.h"
#include "cpu/register.h"

#include <stdio.h>

// flighting
#define SRAM_CACHE_SETTING 0

uint64_t read64bits_dram(uint64_t p_addr) {
  if (SRAM_CACHE_SETTING == 1) {
    return 0x0;
  }

  uint64_t val = 0x0;

  for (int i = 0; i < 8; i++) {
    val += (((uint64_t)mm[p_addr + i]) << (8 * i));
  }

  return val;
}

void write64bits_dram(uint64_t p_addr, uint64_t data) {
  if (SRAM_CACHE_SETTING == 1) {
    return;
  }

  for (int i = 0; i < 8; i++) {
    mm[p_addr + i] = (data >> (8 * i)) & 0xff;
  }
}

void print_register() {
  printf("\n");
  printf("rax = 0x%16lx\trbx = 0x%16lx\trcx = 0x%16lx\trdx = 0x%16lx\n",
         reg.rax, reg.rbx, reg.rcx, reg.rdx);
  printf("rsi = 0x%16lx\trdi = 0x%16lx\trbp = 0x%16lx\trsp = 0x%16lx\n",
         reg.rsi, reg.rdi, reg.rbp, reg.rsp);
  printf("rip = 0x%16lx\t", reg.rip);
  printf("\n");
}

void print_stack() {
  int n = 10;

  uint64_t *high = (uint64_t *)&mm[va2pa(reg.rsp)];
  high = &high[n];

  uint64_t rsp_start = reg.rsp + 8 * n;

  printf("\n");
  for (int i = 0; i < 2 * n; i++) {
    uint64_t *ptr = (uint64_t *)(high - i);
    printf("0x%lx : 0x%16lx", rsp_start, (uint64_t)*ptr);

    if (i == n) {
      printf(" <== rsp");
    }

    rsp_start -= 8;

    printf("\n");
  }
  printf("\n");
}