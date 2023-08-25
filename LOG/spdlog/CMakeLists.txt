cmake_minimum_required(VERSION 3.5)

set(EXECUTABLE ${EXECUTABLE} main)

project(${EXECUTABLE} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-I../ -Wall -g -std=c++11")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}")
set(CMAKEFILES ${PROJECT_SOURCE_DIR}/build/Makefile)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

find_package(Threads REQUIRED)
aux_source_directory(. DIR_SRCS)
add_executable(${EXECUTABLE} ${DIR_SRCS})
target_link_libraries(${EXECUTABLE} Threads::Threads)
# file(COPY ${CMAKEFILES} DESTINATION ${CMAKE_CURRENT_SOURCE_FILE})