#include "../RCPython/VeloComm.hpp"
#include "RCObjects/BMS.hpp"
#include "RCObjects/GPSdata.hpp"
#include "RCObjects/Motor.hpp"
//#include "RCAcquisition.hpp"
// void UpdateGarminLoop(Garmin18Reader * test1)
// {
//   while(1)
//   {
//     test1->Update();
//     std::cout << "Latitude: " << test1->GetGPSData().GetLatitude() << std::endl
// 	<< "Speed: " << test1->GetGPSData().GetSpeed() << std::endl
// 	<< "Longitude: " << test1->GetGPSData().GetLongitude()
// 	<< std::endl;
//
//     boost::this_thread::sleep(boost::posix_time::seconds(3));
//   }
// }
//
// void UpdateLithiumateLoop(LithiumateReader * test2)
// {
//   int i = 0;
//   for(std::vector<Battery>::iterator itr = test2->GetBatteries()->begin(); itr < test2->GetBatteries()->end(); ++itr,++i)
//     std::cout << "Current for battery (" << i << "): " << itr->Getcurrent() << std::endl;
// }

int main()
{
	//RCAcquisition test("./data.log");
	//test.Start();
	BMS testBMS;
	GPSdata testGPS;
	Motor testMotor;
	VeloComm test;
	std::vector<Battery> * testBatteries = testBMS.GetBatteries();
	
	testBatteries->push_back(Battery());
	testBatteries->back().Setcurrent(3.3);
	testBatteries->back().Setresist(2.3);
	testBatteries->back().Settemp(1.3);
	testBatteries->back().Setvolt(0.3);
	
	testBatteries->push_back(Battery());
	testBatteries->back().Setcurrent(1.3);
	testBatteries->back().Setresist(3.3);
	testBatteries->back().Settemp(0.3);
	testBatteries->back().Setvolt(0.3);
	
	testGPS.SetSpeed(10.3);
	testGPS.SetLatitude(2324.2);
	testGPS.SetLongitude(3221.4);
	
	testMotor.SetCurrentAccross(232.4);
	testMotor.SetDutyCycles(340.2);
	testMotor.SetRpm(3400.0);
	testMotor.SetSpeed(34324.4);
	testMotor.SetTemp(3434.23);
	
	test.SetBMSref(&testBMS);
	test.SetGPSref(&testGPS);
	test.SetMotorRef(&testMotor);
	test.Report();
	
	return 0;
}
//   BMS * bms = new BMS();
//   //LithiumateReader * test2 = new LithiumateReader(bms,"/dev/ttyUSB1");
//   GPSdata * gps = new GPSdata();
//   Garmin18Reader * test1 = new Garmin18Reader(gps,"/dev/ttyUSB0");
//   usleep(100000);//the service needs time to get started
// //UpdateLoop(test1);
//   boost::thread thard1(boost::bind(&UpdateGarminLoop,test1));
//   //boost::thread thard2(boost::bind(&UpdateLithiumateLoop,test2));
//   while(1);
//   thard1.interrupt();
//   //thard2.interrupt();
//   delete test1;
//   delete gps;
//   delete bms;
//	return 0;
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
//}