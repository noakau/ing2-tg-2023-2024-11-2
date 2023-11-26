cmake_minimum_required(VERSION 3.23)
project(operationsprojettdg C)

set(CMAKE_C_STANDARD 99)

add_executable(operationsprojettdg main.c operations.h operations.c temps_cycle.h temps_cycle.c)