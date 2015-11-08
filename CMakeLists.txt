cmake_minimum_required(VERSION 2.8.4)
project(minimd)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

set(SOURCE_FILES main.cpp md.cpp)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
add_executable(minimd ${SOURCE_FILES})
