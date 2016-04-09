cmake_minimum_required(VERSION 2.8)

project(pylogger)

set(CMAKE_BUILD_TYPE Debug)

if(UNIX)
include_directories("/usr/include/python2.7/")
endif(UNIX)

macro(add_python_target tgt)
  foreach(file ${ARGN})
    
    get_filename_component(fname ${file} NAME_WE)
    set(OUT ${fname}.pyc)
    
    list(APPEND OUT_FILES ${OUT})
    list(APPEND IN_FILES ${file})
    
    add_custom_target(${OUT} ALL
      COMMAND rm -f ${OUT}
      COMMAND python -m compileall ${file}
      COMMAND cp ${OUT} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${OUT}
      DEPENDS ${OUT_FILES})
      
  endforeach()
  
endmacro()

add_python_target(
    pylogger
    logger.py
    )
    
#include_directories($ENV{QSDK_LOC}/qsdk)
#install(TARGETS pylogger DESTINATION .)