cmake_minimum_required(VERSION 3.18)
project(Mmn_14_algo C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -pedantic -Werror -Wall")

include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(
        Mmn_14_algo
        src/main.c
        src/input.c
        src/heap.c
        src/quick.c
        src/common.c
)