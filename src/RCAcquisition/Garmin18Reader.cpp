#include "Garmin18Reader.hpp"
#include "iGPSReader.hpp"
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <stdlib.h>
#include <boost/thread.hpp>

Garmin18Reader::Garmin18Reader(GPSdata * data, const char * filePath):iGPSReader(data), serialReader(filePath),
	      current_write(0),current_read(0)
{
  serialReader.SetBaud(B38400);			
  serialReader.SetLocal(RAW);
  serialReader.SetParityChecking(NO_PARITY);
  serialReader.SetHardwareFlowControl(false);
  serialReader.SetSoftwareFlowControl(false);
  serialReader.SetOutputOptions(RAW);
  //Set up reading for a "blocking" read. Program will not execute until it receives data.
  serialReader.SetReadOptions(true);
  
  //System config functions
  system("clear");
  system("stty -F /dev/ttyUSB0 sane 38400");
  system("clear");
  
  m_update = new boost::thread(boost::bind(&Garmin18Reader::UpdateLoop,this));
}

Garmin18Reader::~Garmin18Reader()
{
  m_update->interrupt();
}
void Garmin18Reader::UpdateLoop()
{
  while(1)
  {   
   //Find the next frame we can access, and lock it while we write
    while(m_buffers[current_write].lock.try_lock())
      current_write = current_write % 5 ? current_write + 1 : 0;

    //m_buffers[current_write].lock.lock();
/*    std::cout << "reading" << std::endl;*/
    serialReader.Read(m_buffers[current_write].m_buff,70);
/*    std::cout << "read: " << m_buffers[current_write].m_buff << std::endl;*/
    
    m_buffers[current_write].lock.unlock();

    //usleep(300000);
    boost::this_thread::sleep(boost::posix_time::microsec(3000));
  }
}

void Garmin18Reader::Update()
{
/*  std::cout << "Update!" << std::endl;*/
  ParseSentence();
}

void Garmin18Reader::ParseSentence()
{
  int currentRead = current_write;
  currentRead = currentRead -1 > 0 ? currentRead -1:0;
/*  std::cout << "Might get stuck" << std::endl;*/
  m_buffers[0].lock.lock();
  char * locBuff = strdup(m_buffers[0].m_buff);
  m_buffers[0].lock.unlock();
/*  std::cout << "GTFO of the lock" << std::endl;*/
  
  
  char valid, lat_dir, long_dir;
  double lat, longit, speed;
  char * _buffer = strchr(locBuff, ',');
  
/*  std::cout << "_buffer = " << _buffer << std::endl;*/
  strtok(_buffer,"*");
/*  printf("_bufffer: %s\n", _buffer);*/
  
  if(sscanf(_buffer,",%*lf,%c,%lf,%*c,%lf,%*c,%lf,%*lf,%*lf,%*lf,%*c",
	 &valid, &lat, &longit, &speed) < 3)
  {
    GetGPSData().SetValid(false);
/*    printf("Valid?: false\n");*/
  }
  else
  {
    GetGPSData().SetValid(true);
/*    printf("Valid?: true\n");*/
  }
    
  GetGPSData().SetData(speed, lat, longit);
}