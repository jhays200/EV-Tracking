include_directories(${HEADER_DIR}/RCAcquisition)
include_directories(/usr/include/boost-1_42)

find_package(Boost COMPONENTS thread system REQUIRED)

set(CPPFILES
    Garmin18Reader.cpp
	iBMSReader.cpp
	iGPSReader.cpp
	LithiumateReader.cpp
	serial.cpp
	main.cpp)

add_executable(RCAcquisition ${CPPFILES})
target_link_libraries(RCAcquisition RCObjects ${Boost_LIBRARIES})