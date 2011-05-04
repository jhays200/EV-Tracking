#include "RCAcquisition/SolitonReader.hpp"
#include "RCObjects/Motor.hpp"
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <stdio.h>
#include <iostream>

SolitonReader::SolitonReader(Motor * data, const char * ip_address, int port)
	: iEMController(data), receiver_endpoint(boost::asio::ip::address_v4::from_string(ip_address), port),
	socket(service)
{
}

SolitonReader::~SolitonReader()
{
	socket.close();
}

void SolitonReader::Update()
{
    //udp::endpoint sender_endpoint;
    size_t len = socket.receive_from(
        boost::asio::buffer(buffer), receiver_endpoint);
    
    Parse();
}

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