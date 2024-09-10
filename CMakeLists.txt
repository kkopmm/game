cmake_minimum_required(VERSION 3.10)
project(escape)

# 设置可执行文件的输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})


include_directories(${CMAKE_SOURCE_DIR}/include)
aux_source_directory(${CMAKE_SOURCE_DIR}/src SOURCES)

find_library(easyx easyx ${CMAKE_SOURCE_DIR}/lib)
add_executable(main ${SOURCES})

target_link_libraries(main ${easyx})
target_link_libraries(main winmm)
