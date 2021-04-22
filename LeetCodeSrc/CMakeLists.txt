cmake_minimum_required(VERSION 3.1)
project(CmakeProject)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
set(EXECUTABLE_OUTPUT_PATH ./bin/)
add_executable(Atoi Atoi.cpp)

set(U)