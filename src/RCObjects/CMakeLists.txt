include_directories(${HEADER_DIR}/RCObjects)

set(CPPFILES #testObject.cpp
    Battery.cpp
    BMS.cpp
    GPSdata.cpp
    Motor.cpp
    Time.cpp
    Trip.cpp
	testObject.cpp)

add_library(RCObjects STATIC ${CPPFILES})