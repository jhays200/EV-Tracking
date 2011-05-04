#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include "serial.h"

using namespace std;

int main()
{
  EvSerialIO * serialWriter;
  ifstream gps("gps.txt");
  char buffer[128];
  buffer[127] = 0;
  
  serialWriter = new EvSerialIO("/dev/ttyUSB0");
  serialWriter->SetBaud(B115200);			
  serialWriter->SetLocal(RAW);
  serialWriter->SetParityChecking(NO_PARITY);
  serialWriter->SetHardwareFlowControl(false);
  serialWriter->SetSoftwareFlowControl(false);
  serialWriter->SetOutputOptions(RAW);
  
  while(true)
  {
      printf("Top of loop\n");
      printf("fgets...\n");
      gps >> buffer;
      if(gps.eof())
	gps.seekg(0,ios::beg);
      printf("Got \"%s\" from gps.txt\n",buffer);
      printf("Writing out to /dev/ttyUSB0\n");
      serialWriter->Write(buffer,60);
      usleep(500000);
  }
  
  return 0;
}
 
