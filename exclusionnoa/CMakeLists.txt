cmake_minimum_required(VERSION 3.23)
project(exclusionnoa C)

set(CMAKE_C_STANDARD 99)

add_executable(exclusionnoa exclusion.h exclusion.c main.c)
