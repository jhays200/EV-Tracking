#pragma once
#include "iBMSReader.hpp"
#include "serial.h"

//TODO: Lots of things, but first off optimize and condense
//all the buffers so we don't have to iterate over things
//6 or so times
class LithiumateReader: virtual public iBMSReader
{
public:
  LithiumateReader(BMS * data, const char * filePath);
  virtual void Update();
  
private:
  void Parse();
  
  char context_buffer[32];
  char aux_buffer[23];
  char cell_volt_buffer[100];
  char cell_temp_buffer[100];
  char cell_res_buffer[100];
  
  EvSerialIO serialReader;
};