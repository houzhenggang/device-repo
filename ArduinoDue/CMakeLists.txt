cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE Debug)

project(arduinodue)

add_library(
    arduinodue SHARED 
    arduino_ep.c
    pmc.c 
    uart.c 
    uotghs.c
    )
include_directories($ENV{QSDK_LOC}/qsdk)
install(TARGETS arduinodue DESTINATION .)