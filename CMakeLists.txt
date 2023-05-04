cmake_minimum_required(VERSION 3.25)
project(AnNum1 C)

set(CMAKE_C_STANDARD 17)

add_library(AnNum1 SHARED TP1/rootfinding.h TP1/punto1.c TP1/punto2.c TP1/punto3.c)
