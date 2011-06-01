#pragma once
#include <boost/thread.hpp>

#include "iEMController.hpp"

#include  <stdio.h>
#include  <stdlib.h>
#include  <unistd.h>
#include  <errno.h>
#include  <string.h>
#include  <sys/types.h>
#include  <sys/socket.h>
#include  <netinet/in.h>
#include  <arpa/inet.h>
#include  <netdb.h>

#define MYPORT "48879"
#define MAXBUFLEN 100

enum
  {
    LOG_MSTICS = 1,
    LOG_MINTICS,
    LOG_AUXV,
    LOG_PACKV,
    LOG_CURRENT,
    LOG_TEMP,
    LOG_INPUT3,
    LOG_INPUT2,
    LOG_INPUT1,
    LOG_THROTTLE,
    LOG_CPULOAD,
    LOG_PWM,
    LOG_RPM,
    LOG_RPMERROR,
    LOG_MODE,
    LOG_NUMFIELDS
  };

#define LIMIT_HIMOTORV	0x8000
#define LIMIT_HIMOTORP	0x4000
#define LIMIT_MTEMP	0x2000
#define LIMIT_OVERREV	0x1000

#define LIMIT_LOWPACKV	0x0800
#define LIMIT_HIPACKC	0x0400
#define LIMIT_HVC	0x0200
#define LIMIT_CTEMP	0x0100

#define LIMIT_SLEWRATE	0x0080
#define LIMIT_BLOCKED	0x0040

struct SolitonBuffer
{
	boost::mutex lock;
	char buffer[MAXBUFLEN];
	uint16_t oldmstic;
};


  
/**********************************************
 * Class: SolitonReader
 *
 * Purpose:
 * 	Handles communication and parsing for the
 * 	Soliton motor controller
 **********************************************/
class SolitonReader: public iEMController
{
public:
    SolitonReader(Motor * data);
	~SolitonReader();
    void Update();
private:
	//TODO: Use the message protocol to make CheckError useful
	//void CheckError();
	void Parse();

	void UpdateLoop();

	boost::thread * m_update;

	unsigned short int current_write;
	SolitonBuffer buffer[5];
  
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	int numbytes;
	char buf[MAXBUFLEN];
	uint16_t *debug;
	FILE *log;
};
