#include "VeloComm.hpp"
#include <unistd.h>
#include <cstdio>
#include <RCObjects/BMS.hpp>
#include <RCObjects/GPSdata.hpp>
#include <RCObjects/Motor.hpp>

using namespace std;
using std::string;

const int PYSCRIPT_PATH_LEN = 100;
const int COMMAND_LEN = 30;
// <Testing>
// //GPS
// <Longitude> </Logitude>
// <Laditude>
// <Speed>
// //BMS
// <charge>
// //Battery
// <current#>
// <resist#>
// <temp#>
// <volt#>
// //Motor Data
// <mcurrent>
// <dutycycles>
// <rpm>
// <mspeed>
// <mtemp>
//xml tags to be shipped out

const char * DEVICE_TAG = "<Testing>";
const char * SENSOR_TAGS[] = {//GPS data
							"<Longitude>",
							"<Laditude>",
							"<Speed>",
							//bms data
							"<charge>",
							//motor data
							"<mcurrent>",
							"<dutycycles>",
							"<rpm>",
							"<mspeed>",
							"<mtemp>",
							//battery values
							"<bcurrent%u>",
							"<resist%u>",
							"<temp%u>",
							"<volt%u>"
};
							
const char * DEVICE_ETAG = "</Testing>";
const char * SENSOR_ETAGS[] = {//GPS data
							"</Longitude>",
							"</Laditude>",
							"</Speed>",
							//BMS data
							"</charge>",
							//motor data
							"</mcurrent>",
							"</dutycycles>",
							"</rpm>",
							"</mspeed>",
							"</mtemp>",
							//battery values
							"</bcurrent%u>",
							"</resist%u>",
							"</temp%u>",
							"</volt%u>"
							};
							
enum Sensor
{	//GPS data
	LONGITUDE,
	LADITUDE,
	SPEED,
	//BMS data
	CHARGE,
	//Motor Data
	MCURRENT,
	DUTYCYCLES,
	RPM,
	MSPEED,
	MTEMP,
	//battery values
	BCURRENT,
	RESIST,
	TEMP,
	VOLT
};
							
							
VeloComm::VeloComm(): pModule(0), m_bms(0), m_gps(0), m_motor(0)
{
	string command = "sys.path.append(\"";
	char cwdPath[PYSCRIPT_PATH_LEN];
	
	//getcwd and store it into cwdPath
	
	//create a command to add the script to the path
	getcwd(cwdPath, PYSCRIPT_PATH_LEN); //get current working directory path
	command.append(cwdPath);
	command.append("\")\n");
	printf("%s", command.c_str());
	
	Py_Initialize();
	
	//set the path to the script
	PyRun_SimpleString("import sys\n");
	PyRun_SimpleString(command.c_str());
	PyRun_SimpleString("from VeloComm import Send, Init\n");
	PyRun_SimpleString("Init()\n");
	
}
	

VeloComm::~VeloComm()
{
	//close python interpreter
	Py_Finalize();
}

void VeloComm::SetBMSref(BMS* bms)
{
	m_bms = bms;
}

void VeloComm::SetGPSref(GPSdata* gps)
{
	m_gps = gps;
}

void VeloComm::SetMotorRef(Motor* motor)
{
	m_motor = motor;
}


void VeloComm::Report()
{
	string xmlBody;
	//reserve 300 bytes for the buffer
	xmlBody.reserve(700);
	
	xmlBody = string("Send(\"") + DEVICE_TAG;
	
	AppendGPSstr(xmlBody);
	AppendBMSstr(xmlBody);
	AppendMotorStr(xmlBody);
 	AppendBatteryStr(xmlBody);
	
	//build xml ending
	xmlBody.append(DEVICE_ETAG);
	xmlBody.append("\")\n");
	PyRun_SimpleString(xmlBody.c_str());
	
	m_bms = 0;
	m_gps = 0;
	m_motor = 0;
}

void VeloComm::AppendGPSstr(string& buff)
{
	if(m_gps != 0)
	{
		char buffer[50];
		
		//Longitude
		buff.append(SENSOR_TAGS[LONGITUDE]);
		sprintf(buffer, "%f", m_gps->GetLongitude());
		buff.append(buffer);
		buff.append(SENSOR_ETAGS[LONGITUDE]);
		
		//Laditude
		buff.append(SENSOR_TAGS[LADITUDE]);
		sprintf(buffer, "%f", m_gps->GetLatitude());
		buff.append(buffer);
		buff.append(SENSOR_ETAGS[LADITUDE]);
		
		//Speed
		//Laditude
		buff.append(SENSOR_TAGS[SPEED]);
		sprintf(buffer, "%f", m_gps->GetSpeed());
		buff.append(buffer);
		buff.append(SENSOR_ETAGS[SPEED]);
	}
}

void VeloComm::AppendBatteryStr(string& buff)
{
	if(m_bms != 0)
	{
		unsigned int j = 0;
		for(std::vector<Battery>::iterator i = m_bms->GetBatteries()->begin();
			i != m_bms->GetBatteries()->end();
			++i
		)
			{
				char buffer[50];
				
				//add battery number to tag
				sprintf(buffer, SENSOR_TAGS[BCURRENT], j);
				buff.append(buffer);
				
				//put in current
				sprintf(buffer, "%f", i->Getcurrent());
				buff.append(buffer);
				
				//add battery number to end tag
				sprintf(buffer, SENSOR_ETAGS[BCURRENT], j);
				buff.append(buffer);
				
				//add battery number to tag
				sprintf(buffer, SENSOR_TAGS[RESIST], j);
				buff.append(buffer);
				
				//put in resistance
				sprintf(buffer, "%f", i->Getresist());
				buff.append(buffer);
				
				//add battery number to end tag
				sprintf(buffer, SENSOR_ETAGS[RESIST], j);
				buff.append(buffer);
				
				//add battery number to tag
				sprintf(buffer, SENSOR_TAGS[TEMP], j);
				buff.append(buffer);
				
				//put in temperature
				sprintf(buffer, "%f", i->Gettemp());
				buff.append(buffer);
				
				//add battery number to end tag
				sprintf(buffer, SENSOR_ETAGS[TEMP], j);
				buff.append(buffer);
				
				//add battery number to tag
				sprintf(buffer, SENSOR_TAGS[VOLT], j);
				buff.append(buffer);
				
				//put in temperature
				sprintf(buffer, "%f", i->Getvolt());
				buff.append(buffer);
				
				//add battery number to end tag
				sprintf(buffer, SENSOR_ETAGS[VOLT], j);
				buff.append(buffer);
				
				++j;
			}
	}
}

void VeloComm::AppendBMSstr(string& buff)
{
	if(m_bms != 0)
	{
		char data[30];
		
		buff.append(SENSOR_TAGS[CHARGE]);
		
		sprintf(data, "%u", (int)m_bms->Getcharge());
		buff.append(data);
		
		buff.append(SENSOR_ETAGS[CHARGE]);
	}
}

void VeloComm::AppendMotorStr(string& buff)
{
	if(m_motor != 0)
	{
		char data[30];
		
		buff.append(SENSOR_TAGS[MCURRENT]);
		
		sprintf(data, "%f", m_motor->GetCurrentAccross());
		buff.append(data);
		
		buff.append(SENSOR_ETAGS[MCURRENT]);
		
		buff.append(SENSOR_TAGS[DUTYCYCLES]);
		
		sprintf(data, "%f", m_motor->GetDutyCycles());
		buff.append(data);
		
		buff.append(SENSOR_ETAGS[DUTYCYCLES]);
		
		buff.append(SENSOR_TAGS[RPM]);
		
		sprintf(data, "%f", m_motor->GetRpm());
		buff.append(data);
		
		buff.append(SENSOR_ETAGS[RPM]);
		
		buff.append(SENSOR_TAGS[MSPEED]);
		
		sprintf(data, "%f", m_motor->GetSpeed());
		buff.append(data);
		
		buff.append(SENSOR_ETAGS[MSPEED]);
		
		buff.append(SENSOR_TAGS[MTEMP]);
		
		sprintf(data, "%f", m_motor->GetTemp());
		buff.append(data);
		
		buff.append(SENSOR_ETAGS[MTEMP]);

	}
}


// void VeloComm::Test(double value)
// {
// 	char command[COMMAND_LEN];
// 	sprintf(command, "Test(%f)\n", value);
// 	PyRun_SimpleString(command);
// }

// int main()
// {
// 	VeloComm * test = new VeloComm;
// 	for(int i = 32; i != 0; --i)
// 		test->Test((double)i);
// 	delete test;
// }
