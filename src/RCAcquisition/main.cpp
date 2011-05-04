#include <iostream>
#include <boost/concept_check.hpp>
#include <boost/thread.hpp>
#include "RCAcquisition/Garmin18Reader.hpp"

void UpdateLoop(Garmin18Reader * test1)
{
  while(1)
  {
    std::cout << "Latitude: " << test1->GetGPSData().GetLatitude() << std::endl
	<< "Speed: " << test1->GetGPSData().GetSpeed() << std::endl
	<< "Longitude: " << test1->GetGPSData().GetLatitude()
	<< std::endl;
	
    sleep(10);
  }
}

int main()
{
  GPSdata * gps = new GPSdata();
      Garmin18Reader * test1 = new Garmin18Reader(gps,"/dev/ttyUSB0");

      boost::thread thard(boost::bind(&UpdateLoop,test1));
      std::cout << "Updating: \n";
      while(1);
      thard.interrupt();
      delete test1;
      delete gps;
      return 0;
//  	GPSdata * testGPS;
//  	Garmin18Reader * test2;
// 	ofstream fout("gps.txt");
// 	Motor * testMotor = new Motor;
// 	SolitonReader * test3 = new SolitonReader(testMotor,48873);
      //BMS * testBMS = new BMS;
// 	try
// 	{
// 	  testGPS = new GPSdata;
// 	}
// 	catch(const char * err)
// 	{
// 	  printf("Error: %s", err);
// 	}
      //UpdateCall testCalls[2];
      //LithiumateReader * test1 = new LithiumateReader(testBMS, "/dev/ttyUSB1");
      //printf("Preparing Garmin18Reader...\n");
// 	try
// 	{
// 	  test2 = new Garmin18Reader(testGPS, "/dev/ttyUSB0");
// 	}
// 	catch(const char * err)
// 	{
// 	  std::cerr << "Error: " << err << std::endl;
// 	  return 1;
// 	}
      //printf("Garmin18Reader instantiated\n");
// 	testCalls[0]._call = test2;
// 	testCalls[1]._call = test2;
      
// 	for(;;)
// 	{
	      //boost::thread t1(testCalls[0]);
	      //boost::thread t2(testCalls[1]);
	      
	      //t1.join();
	      //t2.join();
	      
// 		printf("Test2->Update\n");
// 		try
// 		{
// 		  test2->Update();
// 		}
// 		catch(const char * err)
// 		{
// 		 std::cerr << "Usage: client <host>" << std::endl;
// 		  return 1;
// 		}
// 		printf("Test2 updated\n");
// 		printf("Test3 updating\n");
// 		test3->Update();
// 		printf("Test3 updated\n");
// 		cout << "Received data from EMC" << endl
// 		    << "RPM: " << test3->GetMotorData().GetRpm() << endl
// 		    << "Current: " << test3->GetMotorData().GetCurrentAccross() << endl
// 		    << "Temp: " << test3->GetMotorData().GetTemp() << endl;
	      //test1->Update();
	      //cout << "Received data from BMS" << endl
	      //	<< "First battery's resistance: " << (testBMS->GetBatteries())->at(0).Getresist() << endl
	      //	<< "First battery's temp: " <<  testBMS->GetBatteries()->at(0).Gettemp() << endl
	      //	<< "First battery's current: " << testBMS->GetBatteries()->at(0).Getcurrent() << endl;
// 		try
// 		{
// 		  cout << "Yay I win\n" << endl
// 			  << "speed: " << testGPS->GetSpeed()
// 			  << "\nLongitude: " << testGPS->GetLatitude()
// 			  << "\nLatitude: " << testGPS->GetLongitude()
// 			  << endl;
// 		fout << "Yay I win\n" << endl
// 			  << "speed: " << testGPS->GetSpeed()
// 			  << "\nLongitude: " << testGPS->GetLatitude()
// 			  << "\nLatitude: " << testGPS->GetLongitude()
// 			  << endl;
// 		}
// 		catch(const char * err)
// 		{
// 		  std::cerr << "Usage: client <host>" << std::endl;
// 		  return 1;
// 		}
// 		for(std::vector<Battery>::iterator i = testBMS->GetBatteries()->begin();
// 			i != testBMS->GetBatteries()->end();
// 			++i)
// 			{
// 				cout << "Current: " << i->Getcurrent() << endl;
// 				usleep(110000);
// 			}
/*		usleep(300000);*/
// 		printf("Sleeping for a second...\n");
// 		sleep(1);
// 		printf("And go\n");
//	}
      //delete testMotor;
// 	fout.close();
}