#pragma once
#include <boost/thread.hpp>
#include "iBMSReader.hpp"
#include "serial.h"

//This struct allows us to perform reads and writes
//on an array of data, while not overwriting or reading
//from a frame that is already in use by another operation
struct ProBatteryBuf
{
  boost::mutex m_lock;			
  char context_buffer[32];
  char aux_buffer[23];
  char cell_volt_buffer[100];
  char cell_temp_buffer[100];
  char cell_res_buffer[100];
};

/********************************************
 * Class: LithiumateReader
 * 
 * What do?: 
 * 	Handles communication and parsing for the Lithiumate 
 * 	battery management system.
 ********************************************/
//TODO: Lots of things, but first off optimize and condense
//all the buffers so we don't have to iterate over things
//6 or so times
class LithiumateReader: public iBMSReader
{
public:
	LithiumateReader(BMS * data, const char * filePath);
	~LithiumateReader();
	virtual void Update();
  
private:
	void UpdateLoop();

	void Parse();

	unsigned short int current_write;	//Current frame we're writing to
	unsigned short int current_read;	//Current frame we're reading from
	ProBatteryBuf m_buffers[5];		//Array of battery buffers

	EvSerialIO serialReader;		//Serial communication class
	
	boost::thread m_updateLoop;		//Update thread
};