#include "LithiumateReader.hpp"
#include "RCObjects/Battery.hpp"

LithiumateReader::LithiumateReader (BMS * data, const char * filePath) : 
  iBMSReader(data), serialReader ( filePath )
{
    serialReader.SetBaud(B19200);			
    serialReader.SetLocal(RAW);
    serialReader.SetParityChecking(NO_PARITY);
    serialReader.SetHardwareFlowControl(false);
    serialReader.SetSoftwareFlowControl(false);
    serialReader.SetOutputOptions(RAW);
    //Set up reading for a "blocking" read. Program will not execute until it receives data.
    serialReader.SetReadOptions(true);
}

void LithiumateReader::Update()
{
  serialReader.Read(context_buffer,32);
  serialReader.Read(aux_buffer,23);
  serialReader.Read(cell_volt_buffer,100);
  serialReader.Read(cell_temp_buffer,100);
  serialReader.Read(cell_res_buffer,100);
  this->Parse();
}

void LithiumateReader::Parse()
{
	std::vector<Battery> & m_batteries = *GetBatteries();
	
  for(int i(0); i < 100; ++i)
  {
    m_batteries[i].Setcurrent(2+(double)(.001*(int)cell_volt_buffer[i]));
    m_batteries[i].Setresist((double)(100 * (int)cell_res_buffer[i]));
    m_batteries[i].Settemp((float)((int)cell_temp_buffer[i] - 0x80));
  }
}
