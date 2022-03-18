cmake_minimum_required(VERSION 3.21)
project(csapp C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER "/usr/bin/clang")

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE SRC_LISTS 
	${PROJECT_SOURCE_DIR}/src/*.c
)

add_executable(csapp ${SRC_LISTS})
