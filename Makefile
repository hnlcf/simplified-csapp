CC = /usr/bin/gcc-7
CFLAGS = -Wall -g -O2 -Werror -std=gnu99 -Wno-unused-function

GDB = /usr/bin/gdb

BIN = ./bin
EXE = $(BIN)/exe_hardware

SRC_DIR = ./src
CPU = $(SRC_DIR)/hardware/cpu/mmu.c $(SRC_DIR)/hardware/cpu/isa.c
COMMON = $(SRC_DIR)/common/print.c $(SRC_DIR)/common/convert.c
MEMORY = $(SRC_DIR)/hardware/memory/dram.c
MAIN_HARDWARE = $(SRC_DIR)/main_hardware.c

.PHONY:hardware

all: cl fmt hardware run

hardware:
	@$(CC) $(CFLAGS) -I$(SRC_DIR) $(COMMON) $(CPU) $(MEMORY) $(MAIN_HARDWARE) -o $(EXE)

run:
	@$(EXE)

debug: hardware
	@$(GDB) $(EXE)

clean:
	@rm -f $(BIN)/*.o $(BIN)/*~ $(EXE)

fmt: cl
	@cd $(SRC_DIR) && find . -name "*.c" -o -name "*.h" | xargs clang-format -style=file -i

cl: 
	@clear