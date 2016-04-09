cmake_minimum_required(VERSION 2.8)

project(v7mnvic)

set(CMAKE_BUILD_TYPE Debug)

add_library(
    v7mnvic SHARED 
    nvic.c
    )
include_directories($ENV{QSDK_LOC}/qsdk)
install(TARGETS v7mnvic DESTINATION .)