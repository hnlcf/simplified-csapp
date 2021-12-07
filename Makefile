CC = /usr/bin/gcc-7
CFLAGS = -Wall -g -O2 -Werror -std=gnu99

GDB = /usr/bin/gdb

BIN = ./bin
EXE = $(BIN)/program

SRC = ./src
CODE = $(SRC)/*.c $(SRC)/**/*.c
## CODE = $(SRC)/disk/*.c $(SRC)/cpu/*.c $(SRC)/memory/*.c $(SRC)/main.c

.PHONY: program

all: cl fmt csapp run

csapp: 
	@$(CC) $(CFLAGS) -I$(SRC) $(CODE) -o $(EXE)

run:
	@$(EXE)

debug: csapp
	@$(GDB) $(EXE)

clean:
	@rm -f $(BIN)/*.o $(BIN)/*~ $(EXE)

fmt: cl
	@cd $(SRC) && find . -name "*.c" -o -name "*.h" | xargs clang-format -style=file -i

cl: 
	@clear