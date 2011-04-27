#pragma once
#include <string>
#include "iGPSReader.hpp"
#include "serial.h"

class Garmin18Reader:virtual public iGPSReader
{
public:
  Garmin18Reader(GPSdata * data, const char * filePath);
  virtual void Update();
private:
  void ParseSentence();
  
  EvSerialIO serialReader;
  char buffer[128];
};