cmake_minimum_required(VERSION 3.23)
project(precedenceettempscycle C)

set(CMAKE_C_STANDARD 99)

add_executable(precedenceettempscycle operation.h tempscycle.h precedence.h operation.c tempscycle.c precedence.c main.c)


