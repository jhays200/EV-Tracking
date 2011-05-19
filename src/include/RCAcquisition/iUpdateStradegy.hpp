#pragma once
#include <boost/concept_check.hpp>
#include <boost/thread/mutex.hpp>
#define BUFF_SIZE 1024
struct ProBuffer
{
  boost::mutex lock;
  char 	m_buff[256];
};

/****************************************
 * Class: iUpdateStrategy
 * 
 * Purpose:
 * 	Provides a generic Update interface
 * 	for each acquisition module
 ****************************************/
class iUpdateStradegy
{
public:
	virtual ~iUpdateStradegy() { }
	virtual void Update() = 0;
};