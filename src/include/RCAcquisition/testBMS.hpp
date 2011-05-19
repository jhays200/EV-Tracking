#pragma once
#include <boost/thread.hpp>
#include "iBMSReader.hpp"
#include "serial.h"
#include <string>
#include "RCObjects/Battery.hpp"

struct ProBatteryBuf
{
  boost::mutex lock;			
  double buffer[4];
};

class TestBMS: public iBMSReader
{
public:
	TestBMS(BMS * data, const char * filePath);
	~TestBMS();
	virtual void Update();
  
private:
	void UpdateLoop();

	void Parse();
	
	int m_pipe;
	unsigned short int current_write;	//Current frame we're writing to
	ProBatteryBuf m_buffers[5];		//Array of battery buffers
	
	boost::thread * m_update;		//Update thread
	boost::mutex indexLock;
};