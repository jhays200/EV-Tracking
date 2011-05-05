cmake_minimum_required(VERSION 2.8)
project(red_cloud_acq)

#Version information
set(${PROJECT_NAME}_MAJOR_VERSION 0)
set(${PROJECT_NAME}_MINOR_VERSION 3)

#include debug symbols
set(CMAKE_CXX_FLAGS "-g -Wall")

#so we don't have to remember a bunch of paths
set(HEADER_DIR ${red_cloud_acq_SOURCE_DIR}/include)
include_directories(${HEADER_DIR})

#directories that contain libraries to be built

#static libraries
add_subdirectory(RCObjects "./lib")
add_subdirectory(RCPersist)

#executables
add_subdirectory(RCAcquisition "./bin")