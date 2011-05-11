Red-Cloud README

Comments about cmake CMakeLists.txt
	-The src/CMakeLists.txt is our solution
	-CMakeLists.txt files in each subdirectory are projects
	-add_executable compiles a executable
	-target_link_libraries specifies our outside and internal library dependencies
	-add_library compiles a library of either STATIC or SHARED

Implemented Files Currently used
	-Garmin18Reader Class
	-iGPSReader Class
	-RCAcquisition.cpp
	-serial.cpp
	-main.cpp
	-GPSdata.cpp
	

Nonimplemented files in this release
	- iBMSReader.cpp
	- iEMController.cpp
	- SolitonReader.cpp
	- Motor.cpp
	- Battery.cpp
    - BMS.cpp
	- Time.cpp