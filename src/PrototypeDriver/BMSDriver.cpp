#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include "serial.h"

using namespace std;

int main()
{
  EvSerialIO * serialWriter;
  ifstream bms("bms.txt");
  const char space = (char)0x20;
  char context[32];
  char aux[23];
  char cell_volt[100];
  char cell_temp[100];
  char cell_res[100];
  
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
      bms.read(context,32);
      bms.read(aux,23);
      bms.read(cell_volt,100);
      bms.read(cell_temp,100);
      bms.read(cell_res,100);
      if(bms.eof())
	bms.seekg(0,ios::beg);
      serialWriter->Write(context,32);
      serialWriter->Write(aux,23);
      serialWriter->Write(cell_volt,100);
      serialWriter->Write(cell_temp,100);
      serialWriter->Write(cell_res,100);
      sleep(1);
  }
  
  return 0;
}
 
