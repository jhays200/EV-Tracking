#include "Garmin18Reader.hpp"
#include "LithiumateReader.hpp"
#include <boost/thread/thread.hpp>
#include <iostream>
#include <unistd.h>
#include <cstdio>
using std::cout;
using std::endl;

struct UpdateCall
{
	iUpdateStradegy * _call;
	
	void operator()()
	{
		_call->Update();
	}
};


int main()
{
	//BMS * testBMS = new BMS;
	GPSdata * testGPS = new GPSdata;
	//UpdateCall testCalls[2];
	//LithiumateReader * test1 = new LithiumateReader(testBMS, "/dev/ttyUSB1");
	printf("Preparing Garmin18Reader...\n");
	Garmin18Reader * test2 = new Garmin18Reader(testGPS, "/dev/ttyUSB1");
	printf("Garmin18Reader instantiated\n");
// 	testCalls[0]._call = test2;
// 	testCalls[1]._call = test2;
	
	for(;;)
	{
		//boost::thread t1(testCalls[0]);
		//boost::thread t2(testCalls[1]);
		
		//t1.join();
		//t2.join();
		
		printf("Test2->Update\n");
		test2->Update();
		printf("Test2 updated\n");
		
		//cout << "Yay I win\n" << endl;
		cout << "GPSdata Breakdown\n" 
			 << "speed: " << testGPS->GetSpeed()
			 << "\nLongitude: " << testGPS->GetLatitude()
			 << "\nLatitude: " << testGPS->GetLongitude()
			 << "\n\nBMS Breakdown" << endl;
		
			
// 		for(std::vector<Battery>::iterator i = testBMS->GetBatteries()->begin();
// 			i != testBMS->GetBatteries()->end();
// 			++i)
// 			{
// 				cout << "Current: " << i->Getcurrent() << endl;
// 				usleep(110000);
// 			}
		usleep(600000);
	}
	
	
	
	return 0;
}