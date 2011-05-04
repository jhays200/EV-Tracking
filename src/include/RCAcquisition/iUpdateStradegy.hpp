#pragma once
#include <boost/concept_check.hpp>
#include <boost/thread/mutex.hpp>

struct ProBuffer
{
  boost::mutex lock;
  char 	m_buff[256];
};

class iUpdateStradegy
{
public:
	//virtual ~iUpdateStradegy() = 0;
	virtual void Update() = 0;
};