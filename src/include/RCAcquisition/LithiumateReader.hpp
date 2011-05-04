#pragma once
#include <boost/thread.hpp>
#include "iBMSReader.hpp"
#include "serial.h"

struct ProBatteryBuf
{
  boost::mutex m_lock;
  char context_buffer[32];
  char aux_buffer[23];
  char cell_volt_buffer[100];
  char cell_temp_buffer[100];
  char cell_res_buffer[100];
};

//TODO: Lots of things, but first off optimize and condense
//all the buffers so we don't have to iterate over things
//6 or so times
class LithiumateReader: virtual public iBMSReader
{
public:
  LithiumateReader(BMS * data, const char * filePath);
  virtual void Update();
  
private:
  void UpdateLoop();
  
  void Parse();
  
  unsigned short int current_write;
  unsigned short int current_read;
  ProBatteryBuf m_buffers[5];
  
  EvSerialIO serialReader;
};