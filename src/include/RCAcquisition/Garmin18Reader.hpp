#pragma once
#include <boost/thread.hpp>
#include <string>
#include "iGPSReader.hpp"
#include "serial.h"

class Garmin18Reader:public iGPSReader
{
public:
  Garmin18Reader(GPSdata * data, const char * filePath);
  ~Garmin18Reader();
  
  virtual void Update();
  
private:
  void ParseSentence();
  
  void UpdateLoop();
  
  boost::thread * m_update;
  EvSerialIO serialReader;
  
  unsigned short int current_write;
  unsigned short int current_read;
  ProBuffer m_buffers[5];
};