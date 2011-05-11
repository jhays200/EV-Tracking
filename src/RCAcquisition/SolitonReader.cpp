#include "RCAcquisition/SolitonReader.hpp"
#include "RCObjects/Motor.hpp"
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <stdio.h>
#include <iostream>

/******************************************
 * Function: Ctor
 * 
 * Parameters:
 * 	Motor * data - pointer to a motor data object
 * 		for storage purposes
 * 	const char * ip_address - String containing the IP address for boost asio
 * 	int port - Port number the Soliton Motor Controller is communicating on
 ******************************************/
SolitonReader::SolitonReader(Motor * data, const char * ip_address, int port)
	: iEMController(data), receiver_endpoint(boost::asio::ip::address_v4::from_string(ip_address), port),
	socket(service)
{
}

SolitonReader::~SolitonReader()
{
	socket.close();
}

/*************************************
 * Function: Update()
 * 
 * Purpose: Gets the most recent data sent out by 
 * 	the Soliton controller
 *************************************/
void SolitonReader::Update()
{
    //udp::endpoint sender_endpoint;
    size_t len = socket.receive_from(
        boost::asio::buffer(buffer), receiver_endpoint);
    
    Parse();
}

/**********************************************
 * Function: Parse()
 * 
 * Purpose: Parse out the most recent data and push it
 * 	into its appropriate containers
 **********************************************/
void SolitonReader::Parse()
{
  rpm = (short int)buffer[26];
  current = (short int)buffer[10];
  temp = (short int)buffer[12];
  temp *= 10;//C*10
  
  GetMotorData().SetRpm(rpm);
  GetMotorData().SetCurrentAccross(current);
  GetMotorData().SetTemp(temp);
}