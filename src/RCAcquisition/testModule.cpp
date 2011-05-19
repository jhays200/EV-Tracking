#include "testModule.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;
TestModule::TestModule(TestObject * data, const char * filepath)
		:iNamedPipeReader(data)
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
	
	m_update = new boost::thread(boost::bind(&TestModule::UpdateLoop,this));
}

TestModule::~TestModule()
{
	m_update->interrupt();
	m_update->join();
	delete m_update;
	m_update = 0;
}

void TestModule::UpdateLoop()
{
	while(true)
	{
		boost::this_thread::disable_interruption di;
			while(m_buffers[current_write].lock.try_lock())
				current_write = current_write % 5 ? current_write + 1 : 0;
			read(m_pipe,&(m_buffers[current_write].buffer),sizeof(BUFF_SIZE));
			m_buffers[current_write].lock.unlock();
		boost::this_thread::restore_interruption ri(di);
		cout << "Read: " << m_buffers[current_write].buffer << endl;
		boost::this_thread::sleep(boost::posix_time::millisec(200));
	}
}

void TestModule::Update()
{
	int currentRead = current_write;
	currentRead = currentRead -1 > 0 ? currentRead -1:0;
	m_buffers[currentRead].lock.lock();
	double x = atof(m_buffers[currentRead].buffer);
	m_buffers[currentRead].lock.unlock();
	GetData().SetX(x);
}