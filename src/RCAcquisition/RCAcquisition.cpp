#include "RCAcquisition/RCAcquisition.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>

using namespace std;
using namespace boost;

bool RCAcquisition::daemon = false;

RCAcquisition::RCAcquisition(const char * logPath, bool debugMode)
:m_updates(3), m_activeThreads(), m_logFile(0)
//daemon startup code goes here
{
	//if we don't have a log path we need to write to system log
	if(logPath == 0)
	{
		//NOTE implement system log stuff here
		umask(0);
	}
	else
	{
		//Append to log file new data
		m_logFile = fopen(logPath, "w+");
		
		if(!m_logFile)
		{
			printf("Error Unable to open log file");
			exit(EXIT_FAILURE);
		}
	}
}

RCAcquisition::~RCAcquisition()
{
	fclose(m_logFile);
	m_logFile = 0;
	m_updates.clear();
	//NOTE Here is where the threads would need to end
// 	for(vector<boost::thread>::iterator i = m_activeThreads.begin();
// 		i != m_activeThreads.end();
// 		++i)
// 	{
// 		i->join();
// 	}
	
	//m_activeThreads.join_all();
}

//NOTE: Where the show starts
void RCAcquisition::Start()
{
	daemon = true;
	
	//setup daemon and signal handling
	SetupDaemon();
	SetupSignalHadling();
	
	
	while(daemon)
	{
		fprintf(m_logFile, "Hi Guys\n");
		this_thread::sleep(posix_time::seconds(5));
	}
	
	exit(EXIT_SUCCESS);
}

//NOTE: this is where a process can stop the program
void RCAcquisition::Stop(int sig)
{
	switch(sig)
	{
	case SIGQUIT:
	case SIGTERM:
		daemon = false;
		break;
	}
}

void RCAcquisition::SetupDaemon()
{
	pid_t pid, sid;
	
	pid = fork();
	
	
	//exit with failure if unable to create thread
	if(pid < 0)
		exit(EXIT_FAILURE);
	
	//exit with success if we now have two processes
	if(pid > 0)
		exit(EXIT_SUCCESS);
	
	
	
	sid = setsid();
	
	if(!m_logFile)
	{
		printf("Need to implement fully functional daemon");
		exit(EXIT_FAILURE);
	}
	
	if(m_logFile)
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
	}
}

void RCAcquisition::SetupSignalHadling()
{
	signal(SIGQUIT, &RCAcquisition::Stop);
	signal(SIGTERM, &RCAcquisition::Stop);
}

