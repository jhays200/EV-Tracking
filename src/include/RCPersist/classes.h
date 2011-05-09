#include <vector>
using std::vector;

class Motor
{
private:
	double m_currentAcross;
	double m_dutyCycles;
	double m_rpm;
	double m_speed;
	double m_temp;
public:
	~Motor();
	Motor();
	Motor(Motor & motor);
	double GetCurrentAcross();
	double GetDutyCycles();
	double GetRpm();
	double GetSpeed();
	double GetTemp();
	void SetCurrentAcross(double current);
	void SetDutyCycles(double cycles);
	void SetRpm(double rpm);
	void SetSpeed(double speed);
	void SetTemp(double temp);
};

class GPSData
{
	int m_direction;
	double m_latitude;
	double m_longitude;
	float m_speed;
public:
	GPSData();
	~GPSData();
	GPSData(GPSData & rhs);

};

class Battery
{
	int battnum;
	double current;
	double resist;
	float temp;
	double volt;
};

class BMS
{
	double avgBattCurrent;
	double avgBatteryResist;
	double avgBatteryVolt;
	double avgBattTemp;
	int charge;
	vector<Battery> m_batteries;
};
//
//class Trip
//{
//	int m_distance;
//	BMS m_end_bms;
//	m_end
//
//};

