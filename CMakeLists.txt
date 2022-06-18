cmake_minimum_required(VERSION 3.16)
project(csapp
        VERSION 1.0
        LANGUAGES C CXX
        )

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS_DEBUG "-g -Wall -Wextra")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(csapp "")
target_sources(csapp PRIVATE
        "src/main_hardware.c"
        "src/common/convert.c"
        "src/common/print.c"
        "src/hardware/cpu/isa.c"
        "src/hardware/cpu/mmu.c"
        "src/hardware/memory/dram.c"
        )

enable_testing()
add_test(NAME csapp_test COMMAND csapp)
