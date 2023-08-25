project(ftp_client)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -W")
 
include_directories(
    /home/user/codetest/curl-7.62.0/include
)
 
aux_source_directory(./src DIR_SRCS)
 
link_directories(/home/user/codetest/curl-7.62.0/build/lib)
 
add_executable(ftp_client ${DIR_SRCS})
target_link_libraries(ftp_client curl)
