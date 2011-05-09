include_directories(${HEADER_DIR}/RCPersist)
include_directories(/usr/include/mysql)
set(CPPFILES
    dbaseinterface.cpp
    mysqltest.cpp)
#find_library(MYSQL mysqlclient)

add_library(RCPersist STATIC ${CPPFILES})

target_link_libraries(RCPersist mysqlclient)