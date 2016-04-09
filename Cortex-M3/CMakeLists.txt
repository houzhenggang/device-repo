cmake_minimum_required(VERSION 2.8)

project(cortex-m3)

set(CMAKE_BUILD_TYPE Debug)

add_library(
    cortex-m3 SHARED 
    cortex-m3.c
    )
include_directories($ENV{QSDK_LOC}/qsdk)
install(TARGETS cortex-m3 DESTINATION .)