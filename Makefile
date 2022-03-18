CC = /usr/bin/gcc
CFLAGS = -Wall -g -O2 -Werror -std=gnu99 -Wno-unused-function

INCLUDE_DIR = ./include
BIN_DIR = ./build
SRC_DIR = ./src

EXE = $(BIN_DIR)/csapp

# debug
COMMON = $(SRC_DIR)/common/print.c $(SRC_DIR)/common/convert.c

# hardeware
CPU = $(SRC_DIR)/hardware/cpu/mmu.c $(SRC_DIR)/hardware/cpu/isa.c
MEMORY = $(SRC_DIR)/hardware/memory/dram.c

# main
MAIN_HARDWARE = $(SRC_DIR)/main_hardware.c

all: cl fmt hardware run

.PHONY:run clean fmt count cl

hardware:
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $(COMMON) $(CPU) $(MEMORY) $(MAIN_HARDWARE) -o $(EXE)

run: hardware
	@$(EXE)

clean:
	@rm -f $(BIN)/*.o $(BIN)/*~ $(EXE)

fmt: cl
	@find src/ include/ test/ -type f -name '*.c' -o -name '*.h' | xargs -i clang-format -i {}

count: cl
	@find src/ include/ test/ -name '*.[ch]' | xargs wc -l | sort

cl: 
	clear
