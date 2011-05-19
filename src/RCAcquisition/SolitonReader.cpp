#include "RCAcquisition/SolitonReader.hpp"
#include "RCObjects/Motor.hpp"
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <stdio.h>
#include <iostream>
using namespace std;
/******************************************
 * Function: Ctor
 *
 * Parameters:
 * 	Motor * data - pointer to a motor data object
 * 		for storage purposes
 * 	const char * ip_address - String containing the IP address for boost asio
 * 	int port - Port number the Soliton Motor Controller is communicating on
 ******************************************/
SolitonReader::SolitonReader(Motor * data, const char * ip_address, int port):
	iEMController(data),
	service(),
	receiver_endpoint(boost::asio::ip::address_v4::from_string(ip_address), port),
	socket(service),
	current_write(0)
{
	socket.open(udp::v4());
	m_update = new boost::thread(boost::bind(&SolitonReader::UpdateLoop,this));
}

SolitonReader::~SolitonReader()
{
	socket.close();
}

void SolitonReader::Update()
{
	this->Parse();
}
/*************************************
 * Function: UpdateLoop()
 *
 * Purpose: Gets the most recent data sent out by
 * 	the Soliton controller
 *************************************/
void SolitonReader::UpdateLoop()
{
	while(1)
	{
		boost::this_thread::disable_interruption di;
		while(buffer[current_write].lock.try_lock())
			current_write = current_write % 5 ? current_write + 1 : 0;

		size_t len = socket.receive_from(
			boost::asio::buffer(buffer[current_write].buffer),
										 receiver_endpoint);

		buffer[current_write].lock.unlock();

		boost::this_thread::restore_interruption ri(di);
	}
}

/**********************************************
 * Function: Parse()
 *
 * Purpose: Parse out the most recent data and push it
 * 	into its appropriate containers
 **********************************************/
void SolitonReader::Parse()
{
	int currentRead = current_write;
	currentRead = currentRead -1 > 0 ? currentRead -1:0;

	buffer[currentRead].lock.lock();
	char * locBuff = strdup(buffer[currentRead].buffer);
	buffer[currentRead].lock.unlock();

	short int rpm = (short int)locBuff[26];
	short int current = (short int)locBuff[10];
	short int temp = (short int)locBuff[12];
	temp *= 10;//C*10

	GetMotorData().SetRpm(rpm);
	GetMotorData().SetCurrentAccross(current);
	GetMotorData().SetTemp(temp);
	delete [] locBuff;
}