#pragma once
#include <boost/thread.hpp>
#include <string>
#include "iGPSReader.hpp"
#include "serial.h"

/*******************************************
 * Class Name: Garmin18Reader
 * 
 * What do?: 
 * 	Handles Communication and parsing for the Garmin GPS 18 5hz
 *
 ******************************************/
class Garmin18Reader:public iGPSReader
{
public:
  Garmin18Reader(GPSdata * data, const char * filePath);
  ~Garmin18Reader();
  
  virtual void Update();
  
private:
  void ParseSentence();
  
  void UpdateLoop();
  
  boost::thread * m_update;		//update thread
  EvSerialIO serialReader;		//Class used to send and receive data across an RS232 connection
  
  unsigned short int current_write;	//which frame we're reading from
  unsigned short int current_read;	//which frame we're writing to
  ProBuffer m_buffers[5];		//Moving "window" in which we can independently read / write at the same time
};