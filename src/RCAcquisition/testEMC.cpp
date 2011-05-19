#include "testEMC.hpp"
#include <RCObjects/Motor.hpp>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;
TestEMC::TestEMC(Motor * data, const char * filepath):iEMController(data)
{
	if(access(filepath, F_OK) == -1)
	{
		fprintf(stderr, "Failed to access filepath: %s", filepath);
		exit(EXIT_FAILURE);
	}
	m_pipe = open(filepath, O_RDONLY);
	if(m_pipe == -1)
	{
		fprintf(stderr, "Failed to open filepath: %s", filepath);
		exit(EXIT_FAILURE);
	}
	m_update = new boost::thread(boost::bind(&TestEMC::UpdateLoop,this));
}

TestEMC::~TestEMC()
{
	m_update->interrupt();
	m_update->join();
	delete m_update;
	m_update = 0;
}

void TestEMC::UpdateLoop()
{
	while(true)
	{
		boost::this_thread::disable_interruption di;

			while(m_buffers[current_write].lock.try_lock())
				current_write = current_write % 5 ? current_write + 1 : 0;

			read(m_pipe,m_buffers[current_write].buffer,BUFF_SIZE);

			m_buffers[current_write].lock.unlock();
		boost::this_thread::restore_interruption ri(di);
		
		//cout << "Got: " << m_buffers[current_write].buffer << endl;
 		boost::this_thread::sleep(boost::posix_time::microseconds(200000));
	}
}

void TestEMC::Update()
{
	int currentRead = current_write;
	currentRead = currentRead -1 > 0 ? currentRead -1:0;
	
	m_buffers[currentRead].lock.lock();
	double temp[3];
	temp[0] = m_buffers[currentRead].buffer[0];
	temp[1] = m_buffers[currentRead].buffer[1];
	temp[2] = m_buffers[currentRead].buffer[2];
	m_buffers[currentRead].lock.unlock();

	Motor & motor = GetMotorData();
	motor.SetRpm(temp[0]);
	motor.SetSpeed(temp[1]);
	motor.SetTemp(temp[2]);
}