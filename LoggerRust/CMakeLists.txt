cmake_minimum_required(VERSION 2.8)

project(rustlogger)

set(CMAKE_BUILD_TYPE Debug)

add_custom_target(rustlogger ALL
  COMMAND cargo build
  COMMAND cp out/debug/*.so ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
  )

