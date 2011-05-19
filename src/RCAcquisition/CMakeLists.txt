include_directories(${HEADER_DIR}/RCAcquisition)

find_package(Boost COMPONENTS system thread REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(/usr/include/mysql)
set(CPPFILES
    Garmin18Reader.cpp
	iBMSReader.cpp
	iGPSReader.cpp
	LithiumateReader.cpp
	serial.cpp
	iEMController.cpp
	SolitonReader.cpp
<<<<<<< HEAD
	RCAcquisition.cpp
	testModule.cpp
	iNamedPipeReader.cpp
	testBMS.cpp
	testEMC.cpp
=======
	#RCAcquisition.cpp
	#testModule.cpp
	#iNamedPipeReader.cpp
>>>>>>> 4e6d0ec9eb1eaeda93f1b8d994252037349c9071
	main.cpp)

add_executable(RCAcquisition ${CPPFILES})
target_link_libraries(RCAcquisition RCObjects VeloCommLib ${Boost_LIBRARIES})
