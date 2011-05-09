#pragma once
#include <vector>
#include "RCObjects/Time.hpp"
#include <boost/thread.hpp>
#include <cstdio>
#include "RCPersist/dbaseinterface.h"

class iUpdateStradegy;

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
  
  DBaseInterface dbase;
  std::vector<iUpdateStradegy *> m_updates;
  boost::thread_group m_activeThreads;
  FILE * m_logFile;
};