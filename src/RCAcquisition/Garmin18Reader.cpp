#include "Garmin18Reader.hpp"
#include "iGPSReader.hpp"
//#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <stdlib.h>
#include <boost/thread.hpp>

/**************************************************
 * Function: Garmin18Reader::Ctor
 *
 * Parameters:
 * 	GPSData * data - Pointer to a GPSData object to be populated by Update()
 * 	cons char * filepath - Filepath to the GPS (i.e. "/dev/tty*")
 **************************************************/
Garmin18Reader::Garmin18Reader(GPSdata * data, const char * filePath):iGPSReader(data), serialReader(filePath),
	      current_write(0)
{
  //Prepare serial settings
  serialReader.SetBaud(B38400);
  serialReader.SetLocal(OTHER, B38400 | CS8 | CLOCAL | CREAD);
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

  //Startup the update thread
  m_update = new boost::thread(boost::bind(&Garmin18Reader::UpdateLoop,this));
}

Garmin18Reader::~Garmin18Reader()
{
  m_update->interrupt();
  m_update->join();
  delete m_update;
  m_update = 0;
}

/************************************
 * Function: Garmin18Reader::UpdateLoop()
 *
 * purpose: Infinite loop that handles reading from the GPS
 *
 ************************************/
void Garmin18Reader::UpdateLoop()
{
  while(1)
  {
   //Find the next frame we can access, and lock it while we write
   boost::this_thread::disable_interruption di;
    while(m_buffers[current_write].lock.try_lock())
      current_write = current_write % 5 ? current_write + 1 : 0;

    //m_buffers[current_write].lock.lock();
/*    std::cout << "reading" << std::endl;*/
    serialReader.Read(m_buffers[current_write].m_buff,70);
/*    std::cout << "read: " << m_buffers[current_write].m_buff << std::endl;*/

    m_buffers[current_write].lock.unlock();
	boost::this_thread::restore_interruption ri(di);
    //usleep(300000);
    boost::this_thread::sleep(boost::posix_time::microsec(200000));
	//boost::this_thread::interruption_point();
  }

  //exit thread
}

/*********************************************
 * Function: Garmin18Reader::Update()
 *
 * purpose: Overloaded call which handles updating
 * 	local GPS data with the most recent "valid" data
 * 	from the GPS
 *********************************************/
//TODO: -_-' something needs to be done here,
//	probably break up ParseSentence() and
//	modularize it as necessary
void Garmin18Reader::Update()
{
 //std::cout << "Update!" << std::endl;
 ParseSentence();
}

/***************************************
 * Function: Garmin18Reader::ParseSentence()
 *
 * purpose: Identify and collect the most recent valid data
 * 	sample from the GPS, and parse that data into its
 * 	appropriate conatiners
 ***************************************/
void Garmin18Reader::ParseSentence()
{
  int currentRead = current_write;
  currentRead = currentRead -1 > 0 ? currentRead -1:0;
  // std::cout << "Might get stuck" << std::endl;
  //boost::this_thread::disable_interruption di;
  m_buffers[currentRead].lock.lock();
  //std::cout << "Locked" << std::endl;
  char * locBuff = strdup(m_buffers[currentRead].m_buff);
  //std::cout << "Unlocking" << std::endl;
  m_buffers[currentRead].lock.unlock();
  //boost::this_thread::restore_interruption ri(di);
  //std::cout << "GTFO of the lock" << std::endl;

  char valid;
  char north, east;
  double lat, longit, speed;
  double unchangedlatitude, unchangedlongitude;
  int num;
  char * _buffer = strchr(locBuff, ',');

/*  std::cout << "_buffer = " << _buffer << std::endl;*/
  strtok(_buffer,"*");
/*  printf("_bufffer: %s\n", _buffer);*/

  if(sscanf(_buffer,",%*lf,%c,%lf,%c,%lf,%c,%lf,%*lf,%*lf,%*lf,%*c",
	 &valid, &unchangedlatitude,&north, &unchangedlongitude,&east, &speed) < 3)
  {
    GetGPSData().SetValid(false);
/*    printf("Valid?: false\n");*/
  }
  else
  {
    GetGPSData().SetValid(true);
/*    printf("Valid?: true\n");*/
  }

	unchangedlatitude = unchangedlatitude / 100;
	num = unchangedlatitude;
	lat = num + (( (unchangedlatitude - num )/60) * 100);
	unchangedlongitude = unchangedlongitude / 100;
	num = unchangedlongitude;
	longit = num + (( (unchangedlongitude - num)/60) * 100);
	if (north == 'S')
		lat = - lat;
	if (east == 'W')
		longit = - longit;

  GetGPSData().SetData(speed, lat, longit);
  delete [] locBuff;
  //boost::this_thread::interruption_point();
}