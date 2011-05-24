#cmake_minimum_required(VERSION 2.8)
#project(python_test)

include_directories("/usr/include/boost/")
include(${CMAKE_SOURCE_DIR})

#copy python file to binary dir
file(COPY VeloComm.py DESTINATION ${CMAKE_BINARY_DIR}/bin)

add_library(VeloCommLib STATIC VeloComm.cpp)
target_link_libraries(VeloCommLib python2.7 RCObjects)