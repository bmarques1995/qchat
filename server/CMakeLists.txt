cmake_minimum_required(VERSION 3.28)

if(NOT CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
    message(FATAL_ERROR "this project only works on Linux")
endif()

project(qchat VERSION 1.0 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/")

include(dep_tracer)
include(target_destination)

add_subdirectory(src)
