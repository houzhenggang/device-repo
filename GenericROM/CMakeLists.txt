cmake_minimum_required(VERSION 2.8)

project(generic-rom)

set(CMAKE_BUILD_TYPE Debug)

add_library(
    generic-rom SHARED 
    generic-rom.c
    )
include_directories($ENV{QSDK_LOC}/qsdk)
install(TARGETS generic-rom DESTINATION .)