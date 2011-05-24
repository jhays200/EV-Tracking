#pragma once
#include <boost/thread.hpp>
#include "iEMController.hpp"

struct TestBuffer
{
	boost::mutex lock;
	char buffer[BUFF_SIZE];
};

class TestEMC: public iEMController
{
public:
    TestEMC(Motor * data, const char * filepath);
	~TestEMC();
    void Update();
private:
  void UpdateLoop();
  int m_pipe;
  boost::thread * m_update;

  unsigned short int current_write;
  TestBuffer m_buffers[5];
};