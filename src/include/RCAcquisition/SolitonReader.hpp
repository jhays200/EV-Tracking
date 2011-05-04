#pragma once
#include <boost/asio.hpp>
using boost::asio::ip::udp;

#include "iEMController.hpp"
const int SOLITON_PORT = 48879;

const int MAXBUFLEN = 100;

//Error / status codes
const int STARTING_UP =	 			0b0000000000000000;
const int PRECHARGING =	 			0b0000000000000001;
const int ENGAGING_CONTACTORS =		0b0000000000000010;
const int	WAITING_FOR_START_STIG=	0b0000000000000011;
const int	THROTTLE_NOT_ZERO=		0b0000000000000100;
const int	RUNNING	=				0b0000000000000101;
//6-18 not used
const int	ADC_OUT_OF_RANGE =		0b0000000000010011;
const int	CURRENT_SENSOR_FAILURE=	0b0000000000010100;
const int	ZERO_VOLT_AFTER_PCHARGE=0b0000000000010101;
//NOTE damnit jeff

const int	FAULTY_THROTTLE_SIGNAL=	0b0000000000010111;
const int	V12_TOO_HIGH=			0b0000000000011000;
const int	V12_TOO_LOW=			0b0000000000011001;
const int	PVOLTAGE_TOO_HIGH=		0b0000000000011010;
const int	PVOLTAGE_TOO_LOW=		0b0000000000011011;
const int IGBT_DESATURATION=		0b0000000000011100;
const int	OUT_OF_MEMORY=			0b0000000000011101;
const int	SOFTWARE_ERROR=			0b0000000000011110;
const int	USER_SHUTDOWN=			0b0000000000011111;

//Mode codes
const int	THROTTLE_BLOCKED=	 	0b0000000001000000;
const int	SLEWRATE_ON=		 	0b0000000010000000;
const int HIGH_CONTROLELR_TEMP=		0b0000000100000000;
const int	HIGH_VOLTAGE_CURRENT=	0b0000001000000000;
const int	HIGH_PACK_CURRENT=	 	0b0000010000000000;
const int LOW_PACK_VOLTAGE=	 		0b0000100000000000;
const int OVER_REV=		 			0b0001000000000000;
const int	HIGH_MOTOR_TEMP=		0b0010000000000000;
const int	HIGH_MOTOR_POWER=	 	0b0100000000000000;
const int	HIGH_MOTOR_VOLTAGE=	 	0b1000000000000000;

class SolitonReader: public iEMController
{
public:
    SolitonReader(Motor * data, const char * ip_address = "127.0.0.1", int port = SOLITON_PORT);
    void Update();
    
private:
  //TODO: Use the message protocol to make CheckError useful
  //void CheckError();
  void Parse();
  
  boost::asio::io_service service;
  udp::endpoint receiver_endpoint;
  udp::socket socket;
  
  char	buffer[30];
  double rpm;
  double current;
  double temp;
};