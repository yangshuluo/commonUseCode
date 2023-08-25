######################
[[这里面的是方法,选择使用]]
######################

# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.5)

# 项目信息 语言c++
project (demo LANGUAGES CXX)

#标准c++11
set (CMAKE_CXX_STANDARD 11)

#设置c++编译选项
set (CMAKE_CXX_FLAGS "-Wall -g")

#设置编译类型是release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# 提示信息
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# 加入一个配置头文件，用于处理 CMake 对源码的设置
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )

# 设置可执行文件输出路径    
set (EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

# 设置生产库路径
set (LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/lib")

# 是否使用自己的 MathFunctions 库
option (USE_MYMATH
       "Use provided math implementation" ON)

#message([STATUS|WARNING|AUTHOR_WARNING|FATAL_ERROR|SEND_ERROR] "message to display" ...)
message(STATUS "Complie sources into a libaray? ${USE_MYMATH}")

# 是否加入 MathFunctions 库
if (USE_MYMATH)
  #将指定目录添加到编译器的头文件搜索路径之下，指定的目录被解释成当前源码路径的相对路径。
  #相关命令target_include_directories
  include_directories ("${PROJECT_SOURCE_DIR}/math")
  #添加子目录
  add_subdirectory (math) 
  #设置变量 
  set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif (USE_MYMATH)

# 将各个c文件保存到SRC_LIST变量 
set(SRC_LIST add.c div.c main.c mult.c sub.c) 

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 查找方式2 file  file(GLOB/GLOB_RECURSE 变量名 要搜索的文件路径和文件类型)
# GLOB: 将指定目录下搜索到的满足条件的所有文件名生成一个列表，并将其存储到变量中。
# GLOB_RECURSE：递归搜索指定目录，将搜索到的满足条件的文件名生成一个列表，并将其存储到变量中。
file(GLOB MAIN_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB MAIN_HEAD ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

# 拼接1 set 
file(GLOB SRC_1 ${PROJECT_SOURCE_DIR}/src1/*.cpp)
file(GLOB SRC_2 ${PROJECT_SOURCE_DIR}/src2/*.cpp)
# 追加(拼接)
set(SRC_1 ${SRC_1} ${SRC_2} ${TEMP})
message(STATUS "message: ${SRC_1}")

#拼接2 list  list还可以移除不需要编译的文件通过第一个参数 REMOVE_ITEM ...
file(GLOB SRC_1 ${PROJECT_SOURCE_DIR}/src1/*.cpp)
file(GLOB SRC_2 ${PROJECT_SOURCE_DIR}/src2/*.cpp)
# 追加(拼接)
list(APPEND SRC_1 ${SRC_1} ${SRC_2} ${TEMP})
message(STATUS "message: ${SRC_1}")


# 指定生成目标
add_executable (demo ${DIR_SRCS})

# 包含库路径
link_directories(${PROJECT_SOURCE_DIR}/lib)

# 动态库和静态库生成 add_library(库名称 STATIC/SHARED 源文件1 [源文件2] ...) 
add_library(calc STATIC ${SRC_LIST})  #静态库 libcalc.a
add_library(calc SHARED ${SRC_LIST})  #动态库 libcalc.so

# 链接thread库 动态库链接
find_package(Threads REQUIRED)
target_link_libraries(demo Threads::Threads)

# 静态库链接
link_libraries(demo)

# 设置安装路径前缀
set (CMAKE_INSTALL_PREFIX ../)

# 安装<文件类型><文件><安装路径>
install (TARGETS demo DESTINATION bin)
install (FILES 
        "${PROJECT_BINARY_DIR}/config.h"
        DESTINATION include)
install (FILES config.h.in DESTINATION config)

# 宏定义 在代码中定义一个DEBUG的宏
add_definitions(-DDEBUG)

# 常用的路径宏
#########################[[
PROJECT_SOURCE_DIR	使用 cmake 命令后紧跟的目录，一般是工程的根目录
PROJECT_BINARY_DIR	执行 cmake 命令的目录
CMAKE_CURRENT_SOURCE_DIR	当前处理的 CMakeLists.txt 所在的路径
CMAKE_CURRENT_BINARY_DIR	target 编译目录
EXECUTABLE_OUTPUT_PATH	重新定义目标二进制可执行文件的存放位置
LIBRARY_OUTPUT_PATH	重新定义目标链接库文件的存放位置
PROJECT_NAME	返回通过 PROJECT 指令定义的项目名称
CMAKE_BINARY_DIR	项目实际构建路径，假设在 build 目录进行的构建，那么得到的就是这个目录的路径
]]#######################


###############
[[多层嵌套目录
参考链接:https://subingwen.cn/cmake/CMake-advanced/#1-%E5%B5%8C%E5%A5%97%E7%9A%84CMake
]]
#################