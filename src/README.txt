Red-Cloud README

Header Files are located in the associated matching folders
	in the include directory.

Comments about cmake CMakeLists.txt
	-The src/CMakeLists.txt is our solution
	-CMakeLists.txt files in each subdirectory are projects
	-add_executable compiles a executable
	-target_link_libraries specifies our outside and internal library dependencies
	-add_library compiles a library of either STATIC or SHARED

Implemented Files
	-TestScript.py
	-Garmin18Reader Class
	-iGPSReader Abstract Class
	-RCAcquisition Class
	-serial Class
	-main.cpp
	-GPSdata Class
	-mysqlinterface
	-dbaseinterface
	-mysqltest class
	-iUpdateStradegy interface

Nonimplemented files in this release
	- iBMSReader.cpp
	- iEMController.cpp
	- SolitonReader.cpp
	- Motor.cpp
	- Battery.cpp
    - BMS.cpp
	- Time.cpp
	-other files not listed in Implemented Files release
	
Folders to Ignore
	- RCCommunication isn't used to compile our system and
		is an old folder.