cmake_minimum_required(VERSION 2.8)

project(loggerc)

set(CMAKE_BUILD_TYPE Debug)

add_library(
    loggerc SHARED 
    logger.c
    )
include_directories($ENV{QSDK_LOC}/qsdk)
install(TARGETS loggerc DESTINATION .)