#pragma once
#include "iNamedPipeReader.hpp"
#include "RCObjects/testObject.hpp"
#include <boost/thread.hpp>

struct TestBuff
{
	char buffer[256];
	boost::mutex lock;
};

class TestModule:public iNamedPipeReader
{
public:
  TestModule(TestObject * data, const char * filePath);
  ~TestModule();

  virtual void Update();

private:
  void UpdateLoop();

  int m_pipe;
  
  boost::thread * m_update;

  unsigned short int current_write;
  TestBuff m_buffers[5];
};