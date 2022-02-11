CC = gcc
CFLAGS = -Wall -g -O0 -Werror -std=gnu99 -Wno-unused-function

GDB = gdb

BIN = ./build
EXE = $(BIN)/csapp

INCLUDE_DIR = ./include
SRC_DIR = ./src
CPU = $(SRC_DIR)/hardware/cpu/mmu.c $(SRC_DIR)/hardware/cpu/isa.c
COMMON = $(SRC_DIR)/common/print.c $(SRC_DIR)/common/convert.c
MEMORY = $(SRC_DIR)/hardware/memory/dram.c
MAIN_HARDWARE = $(SRC_DIR)/main_hardware.c

.PHONY:hardware

all: cl fmt hardware run

hardware:
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $(COMMON) $(CPU) $(MEMORY) $(MAIN_HARDWARE) -o $(EXE)

run:
	$(EXE)

debug: hardware
	$(GDB) $(EXE)

clean:
	rm -f $(BIN)/*.o $(BIN)/*~ $(EXE)

fmt: cl
	sh codeformat.sh

count: cl
	sh countlines.sh

cl: 
	clear
