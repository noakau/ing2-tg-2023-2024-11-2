cmake_minimum_required(VERSION 3.23)
project(exclusion_TempsdeCycle C)

set(CMAKE_C_STANDARD 99)

add_executable(exclusion_TempsdeCycle main.c cmake-build-debug/operations.c operations.h cmake-build-debug/temps_cycle.c cmake-build-debug/temps_cycle.h cmake-build-debug/exclusion.h cmake-build-debug/exclusion.c)
