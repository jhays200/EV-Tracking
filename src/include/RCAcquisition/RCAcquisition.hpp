#pragma once
#include <vector>
#include "RCObjects/Time.hpp"
#include <boost/thread.hpp>
#include <cstdio>
#include "RCPersist/dbaseinterface.h"

class iUpdateStradegy;

/**************************************************************************
* Class: RCAcquisition
*
*Public Functions:
*	RCAcquisition(const char * logPath = 0, bool debugMode = false)
*		This is the ctor for our system and sets up a log file to
*		be used for error logging.
*
*	~RCAcquisition();
*		This file closes the log file and clears out m_updates.
*
*	void Start();
*		Starts the program's event loop.
*
*	static void Stop(int sig);
*		Handles the signals sent by the User to stop the system.
*
*	void SetupDaemon();
*		Sets up a daemon process by forking the process, reassigning the
*		process id, and closes stdin, stdout, and stderr.
*
*	static void SetupSignalHadling();
*		Sets up signal handling for SIGTERM and SIGQUIT.
***************************************************************************/
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

  //DBaseInterface dbase;
  std::vector<iUpdateStradegy *> m_updates;
  boost::thread_group m_activeThreads;
  FILE * m_logFile;
};