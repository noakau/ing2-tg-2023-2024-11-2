cmake_minimum_required(VERSION 3.23)
project(Integration C)

set(CMAKE_C_STANDARD 99)

add_executable(Integration main.c exclusion.h temps_de_cycleAndOperation.h precedense.h exclusion.c TempsCycleAndOperation.c Precedense.c)
