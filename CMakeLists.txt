cmake_minimum_required(VERSION 3.25)
project(AnNum1 C)

set(CMAKE_C_STANDARD 17)

add_library(AnNum1 SHARED TP1/*.c TP1/*.h TP1/csvwriter.h)
