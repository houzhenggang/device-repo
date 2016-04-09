cmake_minimum_required(VERSION 2.8)

project(libtest_project)

set(FROM_MASTER_SCRIPT 1)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS "${CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS} -undefined dynamic_lookup")
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

add_subdirectory(./ArduinoDue)

add_subdirectory(./ARMv7M-NVIC)
add_subdirectory(./Cortex-M3)
add_subdirectory(./GenericRAM)
add_subdirectory(./GenericROM)
add_subdirectory(./MemoryAlias)

add_subdirectory(./LoggerC)
add_subdirectory(./LoggerPython)
add_subdirectory(./LoggerRust)

include_directories($ENV{QSDK_LOC}/qsdk)