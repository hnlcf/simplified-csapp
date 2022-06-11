cmake_minimum_required(VERSION 3.16)
project(csapp C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-g -Wall -Wextra -Werror -Wpedantic")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SRC_LISTS
        src/main_hardware.c
        src/common/convert.c
        src/common/print.c
        src/hardware/cpu/isa.c
        src/hardware/cpu/mmu.c
        src/hardware/memory/dram.c
        )

add_executable(csapp ${SRC_LISTS})
