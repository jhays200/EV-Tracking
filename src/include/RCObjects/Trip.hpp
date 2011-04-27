///////////////////////////////////////////////////////////
//  Trip.hpp
//  Implementation of the Class Trip
//  Created on:      20-Apr-2011 12:19:34 AM
//  Original author: jon
///////////////////////////////////////////////////////////

#if !defined(EA_E534AA8C_D13E_44ed_9F16_515DB8B32FF3__INCLUDED_)
#define EA_E534AA8C_D13E_44ed_9F16_515DB8B32FF3__INCLUDED_

#include <ctime>
#include "BMS.hpp"
#include "GPSdata.hpp"

class Trip
{

public:
	Trip();

// 	Trip(int tripID);
	Trip(const Trip & copy);
	virtual ~Trip();
	void EndTrip();
	int GetDistance();
	time_t GetEnd_t();
	time_t GetStart_t();
	time_t GetStart_Time();
// 	int GetTripID();
	Trip & operator=(const Trip & copy);
	void SaveLocPoint(GPSdata location);
	void SetDistance(int newVal);
	void SetEnd_t(time_t newVal);
	void SetStart_t(time_t newVal);
	void StartTrip();

private:
	int m_distance;
	BMS m_end_bms;
	BMS m_start_bms;
	time_t m_end_t;
	time_t m_start_t;
	GPSdata m_start_loc;
	GPSdata m_stop_loc;
	//const int m_tripID;

};
#endif // !defined(EA_E534AA8C_D13E_44ed_9F16_515DB8B32FF3__INCLUDED_)
