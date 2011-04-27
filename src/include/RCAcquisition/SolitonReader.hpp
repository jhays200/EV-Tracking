#pragma once
#include <boost/asio.hpp>
using boost::asio::ip::udp;

#include "iEMController.hpp"
#define SOLITON_PORT 48879

#define MAXBUFLEN 100

//Error / status codes
#define STARTING_UP	 	0000000000000000b
#define PRECHARGING	 	0000000000000001b
#define	ENGAGING_CONTACTORS	0000000000000010b
#define	WAITING_FOR_START_STIG	0000000000000011b
#define	THROTTLE_NOT_ZERO	0000000000000100b
#define	RUNNING			0000000000000101b
//6-18 not used
#define	ADC_OUT_OF_RANGE	0000000000010011b
#define	CURRENT_SENSOR_FAILURE	0000000000010100b
#define	ZERO_VOLT_AFTER_PCHARGE	0000000000010101b
#define	PVOLTAGE_TOO_LOW	0000000000010110b
#define	FAULTY_THROTTLE_SIGNAL	0000000000010111b
#define	12V_TOO_HIGH		0000000000011000b
#define	12V_TOO_LOW		0000000000011001b
#define	PVOLTAGE_TOO_HIGH	0000000000011010b
#define	PVOLTAGE_TOO_LOW	0000000000011011b
#define IGBT_DESATURATION	0000000000011100b
#define	OUT_OF_MEMORY		0000000000011101b
#define	SOFTWARE_ERROR		0000000000011110b
#define	USER_SHUTDOWN		0000000000011111b

//Mode codes
#define	THROTTLE_BLOCKED	 0000000001000000b
#define	SLEWRATE_ON		 0000000010000000b
#define HIGH_CONTROLELR_TEMP	 0000000100000000b
#define	HIGH_VOLTAGE_CURRENT	 0000001000000000b
#define	HIGH_PACK_CURRENT	 0000010000000000b
#define LOW_PACK_VOLTAGE	 0000100000000000b
#define OVER_REV		 0001000000000000b
#define	HIGH_MOTOR_TEMP		 0010000000000000b
#define	HIGH_MOTOR_POWER	 0100000000000000b
#define	HIGH_MOTOR_VOLTAGE	 1000000000000000b

class SolitonReader: virtual public iEMController
{
public:
    SolitonReader(Motor * data, int port = SOLITON_PORT);
    void Update();
    
private:
  //TODO: Use the message protocol to make CheckError useful
  //void CheckError();
  void Parse();
  
  boost::asio::io_service io_service;
  udp::endpoint receiver_endpoint;
  udp::socket socket;
  
  char	buffer[30];
  double rpm;
  double current;
  double temp;
};