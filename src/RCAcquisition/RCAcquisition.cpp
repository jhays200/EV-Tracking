#include "RCAcquisition/RCAcquisition.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>
#include "RCAcquisition/Garmin18Reader.hpp"
#include "RCAcquisition/LithiumateReader.hpp"

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
		//NOTE: implement system log stuff here
		umask(0);
	}
	else
	{
		//Append to debug log file new data for
		//error reporting.
		m_logFile = fopen(logPath, "w+");
		
		if(!m_logFile)
		{
			printf("Error Unable to open log file");
			exit(EXIT_FAILURE);
		}
	}
}

//take care of some house keeping.
RCAcquisition::~RCAcquisition()
{
	fclose(m_logFile);
	m_logFile = 0;
	m_updates.clear();

}

//NOTE: Where the show starts
void RCAcquisition::Start()
{
	GPSdata dataGPS;
	BMS dataBM;
	
	daemon = true;
	
	//setup daemon and signal handling
	//SetupDaemon();
	SetupSignalHadling();
	printf("Made it past signal setup\n");
	
	//construct update classes
	m_updates[0] = new Garmin18Reader(&dataGPS, "/dev/ttyUSB0");
	//m_updates[1] = new LithiumateReader(&dataBM, "/dev/ttyUSB1");
	printf("Made it the Garmin Setup\n");
	boost::this_thread::sleep(boost::posix_time::millisec(750));
	
	while(daemon)
	{
		m_activeThreads.create_thread(boost::bind(&iUpdateStradegy::Update, m_updates[0]));
		//m_activeThreads.create_thread(boost::bind(&iUpdateStradegy::Update, m_updates[1]));
		m_activeThreads.join_all();
		
		printf("\nLatitude: %f\n", dataGPS.GetLatitude());
		printf("Speed: %f\n", dataGPS.GetSpeed());
		printf("Longitude: %f\n", dataGPS.GetLongitude());
		dbase.GPSInsert(dataGPS.GetLatitude(),dataGPS.GetLongitude(),dataGPS.GetSpeed());
		
		boost::this_thread::sleep(boost::posix_time::millisec(500));
	}
	
	fprintf(m_logFile, "Made it outside the loop\n");
	
	delete m_updates[0];
	m_updates[0] = 0;
	//delete m_updates[1];
	
	exit(EXIT_SUCCESS);
}

//NOTE: this is where the user can signal the program
		//to quite.
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

//NOTE: This isn't used for debugging because it changes
	//the process id for our system.  This makes it harder
	//to automate testing for later on but will be implemented
	//used for the final release.
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

//This setup the signals being sent to 
	//&RCAcquisition::Stop(int sig)
void RCAcquisition::SetupSignalHadling()
{
	signal(SIGQUIT, &RCAcquisition::Stop);
	signal(SIGTERM, &RCAcquisition::Stop);
}

