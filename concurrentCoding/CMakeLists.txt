cmake_minimum_required(VERSION 3.5)

set(EXECUTABLE ${EXECUTABLE} main)

project(${EXECUTABLE})

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-Wall")

include_directories(
    "${RPOJECT_SOURCE_DIR}/include"
)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

message(STATUS "PROJECT_SOURCE_DIR is ${PROJECT_SOURCE_DIR}")

#查找第三方包
find_package(Threads)

aux_source_directory(. DIR_SRCS)

add_executable(${EXECUTABLE} ${DIR_SRCS})

target_link_libraries(${EXECUTABLE} ${CMAKE_THREAD_LIBS_INIT})

set(CMAKE_INSTALL_PREFIX ../)

install(TARGETS ${EXECUTABLE} DESTINATION bin)