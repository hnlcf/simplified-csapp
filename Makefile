CC = /usr/bin/gcc-7
CFLAGS = -Wall -g -O2 -Werror -std=gnu99

GDB = /usr/bin/gdb

EXE = bin/program

SRC = ./src
CODE = $(SRC)/*.c $(SRC)/**/*.c
## CODE = $(SRC)/disk/*.c $(SRC)/cpu/*.c $(SRC)/memory/*.c $(SRC)/main.c

.PHONY: program

main: 
	@$(CC) $(CFLAGS) -I$(SRC) $(CODE) -o $(EXE)

run:
	@./$(EXE)

debug: 
	@$(GDB) ./$(EXE)

format:
	@cd $(SRC) && find . -name "*.c" -o -name "*.h" | xargs clang-format -style=file -i