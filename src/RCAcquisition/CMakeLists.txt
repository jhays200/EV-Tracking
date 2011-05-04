include_directories(${HEADER_DIR}/RCAcquisition)


find_package(Boost COMPONENTS system thread REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(CPPFILES
    Garmin18Reader.cpp
	iBMSReader.cpp
	iGPSReader.cpp
	LithiumateReader.cpp
	serial.cpp
	iEMController.cpp
	SolitonReader.cpp
	RCAcquisition.cpp
	main.cpp)

add_executable(RCAcquisition ${CPPFILES})
target_link_libraries(RCAcquisition RCObjects ${Boost_LIBRARIES})
