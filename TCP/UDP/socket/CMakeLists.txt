cmake_minimum_required(VERSION 3.5)

set(CLIENT ${CLIENT} client)
set(SERVER ${SERVER} server)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -g -std=c++11")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/../bin")
set(CMAKEFILES ${PROJECT_SOURCE_DIR}/build/Makefile)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

find_package(Threads REQUIRED)
aux_source_directory(. DIR_SRCS)
add_executable(${CLIENT} client.cpp)
add_executable(${SERVER} server.cpp)