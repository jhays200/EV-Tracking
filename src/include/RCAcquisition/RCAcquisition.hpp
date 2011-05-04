#pragma once
#include <vector>
#include "RCObjects/Time.hpp"
#include "UpdateCall.hpp"
#include <boost/thread.hpp>
#include <cstdio>

class RCAcquisition
{
public:
  RCAcquisition(const char * logPath = 0, bool debugMode = false);
  ~RCAcquisition();
  void Start();
  static void Stop(int sig);
  
private:
	//private methods
	void SetupDaemon();
	static void SetupSignalHadling();
	
	
	//private data stuff
  static bool daemon;
  
  std::vector<UpdateCall> m_updates;
  boost::thread_group m_activeThreads;
  FILE * m_logFile;
};