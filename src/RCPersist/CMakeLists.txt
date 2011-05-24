cmake_minimum_required(VERSION 2.8)
project(RCPersist)

#Version information
set(${PROJECT_NAME}_MAJOR_VERSION 0)
set(${PROJECT_NAME}_MINOR_VERSION 3)

include_directories(${HEADER_DIR}/RCPersist)
include_directories(/usr/include/mysql)

set(CPPFILES
	iRCDatabase.cpp
	RCDatabase.cpp
    )

find_library(MYSQL mysqlclient)

add_library(RCPersist STATIC ${CPPFILES})

target_link_libraries(RCPersist ${MYSQL})