cmake_minimum_required(VERSION 2.8)
project(python_test)


file(COPY VeloComm.py DESTINATION ${CMAKE_BINARY_DIR})
add_executable(test VeloComm.cpp)
target_link_libraries(test python2.7)