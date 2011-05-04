#include "SolitonReader.hpp"
#include "RCObjects/Motor.hpp"
#include <boost/array.hpp>

//using boost::asio::ip::udp;

SolitonReader::SolitonReader(Motor * data, const char * ip_address, int port)
	:iEMController(data), receiver_endpoint(udp::endpoint(boost::asio::ip::address_v4::from_string(ip_address), port)),
	socket(service)
{
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
}