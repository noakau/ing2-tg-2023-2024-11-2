cmake_minimum_required(VERSION 3.23)
project(precedence C)

set(CMAKE_C_STANDARD 99)

add_executable(precedence precedence.c precedenceh.h main.c)
