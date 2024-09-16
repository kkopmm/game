cmake_minimum_required(VERSION 3.10)
project(game)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
# 定义预处理器宏，指定使用 ANSI 版本
add_definitions(-DUNICODE=0 -D_UNICODE=0)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include/easyx)
include_directories(${CMAKE_SOURCE_DIR}/include/common)
include_directories(${CMAKE_SOURCE_DIR}/include/scene)
include_directories(${CMAKE_SOURCE_DIR}/include/utils)


aux_source_directory(${CMAKE_SOURCE_DIR}/src SOURCES)
# 将 lib 目录加入链接器的搜索路径
link_directories(${CMAKE_SOURCE_DIR}/lib)

# add_executable(test ${SOURCES})
add_executable(test ${CMAKE_SOURCE_DIR}/test.cpp ${SOURCES})
add_executable(main ${CMAKE_SOURCE_DIR}/main.cpp ${SOURCES})
