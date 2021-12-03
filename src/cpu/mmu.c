#include "cpu/mmu.h"
#include "memory/dram.h"

uint64_t va2pa(uint64_t v_addr) { return v_addr % MM_LEN; }