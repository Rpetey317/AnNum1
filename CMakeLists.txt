cmake_minimum_required(VERSION 3.25)
project(AnNum1 C)

set(CMAKE_C_STANDARD 17)

add_library(AnNum1 SHARED main.c src/rootfinding.c src/rootfinding.h)
