cmake_minimum_required(VERSION 3.10)
project(game)

# 设置可执行文件的输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})


include_directories(${CMAKE_SOURCE_DIR}/include)
aux_source_directory(${CMAKE_SOURCE_DIR}/src SOURCES)
# 将 lib 目录加入链接器的搜索路径
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(main ${SOURCES})

target_link_libraries(main winmm)