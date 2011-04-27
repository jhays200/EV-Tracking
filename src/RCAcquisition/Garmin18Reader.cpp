#include "Garmin18Reader.hpp"
#include <cstdio>

Garmin18Reader::Garmin18Reader(GPSdata * data, const char * filePath):iGPSReader(data), serialReader(filePath)
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

void Garmin18Reader::Update()
{
  //printf("UPDATE!\n");
  //printf("Beginning read...\n");
  serialReader.Read(buffer,60);
  printf("Read \"%s\"from /dev/ttyUSB1\n",buffer);
  ParseSentence();
}

void Garmin18Reader::ParseSentence()
{
  char valid, lat_dir, long_dir;
  double lat, longit, speed;
  char * _buffer = strchr(buffer, ',');
  strtok(_buffer,"*");
  //printf("Strtok(_buffer,\"*\"); %s\n",_buffer);
  
  if(sscanf(_buffer,",%*lf,%c,%lf,%*c,%lf,%*c,%lf,%*lf,%*lf,%*lf,%*c",
	 &valid, &lat, &longit, &speed) < 4)
  {
    GetGPSData().SetValid(false);
  }
  else
    GetGPSData().SetValid(true);
  
  //printf("%c, %fl, %fl, %fl\n", valid, lat, longit, speed);
  
  GetGPSData().SetData(speed, lat, longit);
}