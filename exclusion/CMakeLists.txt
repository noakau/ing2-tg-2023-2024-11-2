cmake_minimum_required(VERSION 3.23)
project(exclusion C)

set(CMAKE_C_STANDARD 99)

add_executable(exclusion main.c exclusion.h exclusion.c)
