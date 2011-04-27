///////////////////////////////////////////////////////////
//  GPSdata.hpp
//  Implementation of the Class GPSdata
//  Created on:      20-Apr-2011 12:16:35 AM
//  Original author: jonathan.hays
///////////////////////////////////////////////////////////

#if !defined(EA_499C37CF_A8A5_4742_B34F_6D463541F10B__INCLUDED_)
#define EA_499C37CF_A8A5_4742_B34F_6D463541F10B__INCLUDED_

class GPSdata
{

public:
	GPSdata();
	GPSdata(const GPSdata& copy);
	GPSdata(float speed, double latitude, double longitude, int bearing = 0);
	virtual ~GPSdata();
	GPSdata & operator=(const GPSdata & copy);
	int GetBearing() const;
	double GetLatitude() const;
	double GetLongitude() const;
	float GetSpeed() const;
	bool IsValid();
	void SetBearing(int newVal);
	void SetData(float speed, double latitude, double longitude, int bearing = 0);
	void SetLatitude(double newVal);
	void SetLongitude(double newVal);
	void SetSpeed(float newVal);
	void SetValid(bool valid);

private:
	int m_bearing;
	double m_latitude;
	double m_longitude;
	float m_speed;
	bool m_valid;

};
#endif // !defined(EA_499C37CF_A8A5_4742_B34F_6D463541F10B__INCLUDED_)
