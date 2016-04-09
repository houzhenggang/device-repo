cmake_minimum_required(VERSION 2.8)

project(generic-rom)

set(CMAKE_BUILD_TYPE Debug)

add_library(
    memory-alias SHARED 
    memory-alias.c
    )
include_directories($ENV{QSDK_LOC}/qsdk)
install(TARGETS memory-alias DESTINATION .)