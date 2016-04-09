cmake_minimum_required(VERSION 2.8)

project(generic-ram)

set(CMAKE_BUILD_TYPE Debug)

add_library(
    generic-ram SHARED 
    generic-ram.c
    )
include_directories($ENV{QSDK_LOC}/qsdk)
install(TARGETS generic-ram DESTINATION .)