include_directories(${HEADER_DIR}/RCAcquisition)
include_directories(/usr/include/boost-1_42)

find_package(Boost COMPONENTS system REQUIRED)

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
target_link_libraries(RCAcquisition RCObjects ${Boost_SYSTEM_LIBRARY})
set(BOOST_LIBS thread date_time system)
find_package(Boost COMPONENTS ${BOOST_LIBS} REQUIRED)
target_link_libraries(RCAcquisition ${Boost_LIBRARIES})
find_package(Threads REQUIRED)
target_link_libraries(RCAcquisition ${CMAKE_THREAD_LIBS_INIT})
