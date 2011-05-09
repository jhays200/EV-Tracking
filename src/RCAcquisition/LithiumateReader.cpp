#include "LithiumateReader.hpp"
#include "RCObjects/Battery.hpp"
#include <boost/thread.hpp>
#include <boost/bind.hpp>

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
	
	m_updateLoop = boost::thread(boost::bind(&LithiumateReader::UpdateLoop,this));
}

LithiumateReader::~LithiumateReader()
{
	m_updateLoop.interrupt();
	m_updateLoop.join();
}

void LithiumateReader::Update()
{
  this->Parse();
}

void LithiumateReader::UpdateLoop()
{
  while(1)
  {
	  boost::this_thread::disable_interruption di;
	  
    while(m_buffers[current_write].m_lock.try_lock())
      current_write = current_write % 5 ? current_write + 1 : 0;
    
    serialReader.Read(m_buffers[current_write].context_buffer,32);
    serialReader.Read(m_buffers[current_write].aux_buffer,23);
    serialReader.Read(m_buffers[current_write].cell_volt_buffer,100);
    serialReader.Read(m_buffers[current_write].cell_temp_buffer,100);
    serialReader.Read(m_buffers[current_write].cell_res_buffer,100);

    m_buffers[current_write].m_lock.unlock();
	
	boost::this_thread::restore_interruption ri(di);
    
    boost::this_thread::sleep(boost::posix_time::seconds(1));
  }
}

void LithiumateReader::Parse()
{
  int currentRead = current_write;
  currentRead = currentRead -1 > 0 ? currentRead -1:0;
  
  m_buffers[currentRead].m_lock.lock();
  char * local_context_buffer = strdup(m_buffers[currentRead].context_buffer);
  char * local_aux_buffer = strdup(m_buffers[currentRead].aux_buffer);
  char * local_cell_volt_buffer = strdup(m_buffers[currentRead].cell_volt_buffer);
  char * local_cell_temp_buffer = strdup(m_buffers[currentRead].cell_temp_buffer);
  char * local_cell_res_buffer = strdup(m_buffers[currentRead].cell_res_buffer);
  m_buffers[currentRead].m_lock.unlock();

  std::vector<Battery> & m_batteries = *GetBatteries();
	
  for(int i(0); i < 100; ++i)
  {
    m_batteries[i].Setcurrent(2+(double)(.001*(int)local_cell_volt_buffer[i]));
    m_batteries[i].Setresist((double)(100 * (int)local_cell_res_buffer[i]));
    m_batteries[i].Settemp((float)((int)local_cell_temp_buffer[i] - 0x80));
  }
  
  delete [] local_context_buffer;
  delete [] local_aux_buffer;
  delete [] local_cell_volt_buffer;
  delete [] local_cell_temp_buffer;
  delete [] local_cell_res_buffer;
}
