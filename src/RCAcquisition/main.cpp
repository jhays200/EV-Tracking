#include <iostream>
#include <boost/concept_check.hpp>
#include <boost/thread.hpp>
#include "SolitonReader.hpp"
#include "RCObjects/Motor.hpp"

// void UpdateLoop(Garmin18Reader * test1)
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

int main()
{
	Motor testObj;
	iUpdateStradegy * tmp = new SolitonReader(&testObj);
	
	delete tmp;
}