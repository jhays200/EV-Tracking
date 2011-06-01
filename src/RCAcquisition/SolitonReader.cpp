#include "RCAcquisition/SolitonReader.hpp"
#include "RCObjects/Motor.hpp"
char *mode[32] =
  {
    "Starting up",
    "Precharge phase",
    "Engaging contactors",
    "Waiting for startsignal",
    "Throttle not in zero pos",
    "Running",
    "Error 6","Error 7","Error 8","Error 9","Error 10","Error 11","Error 12",
    "Error 13", "Error 14","Error 15","Error 16","Error 17","Error 18",
    "Error: ADC out of range",
    "Error: Current sensor failure",
    "Error: Zero voltage after precharge",
    "Error: Pack voltage too low after precharge",
    "Error: Faulty throttle signal",
    "Error: 12 Volt too high",
    "Error: 12 Volt too low",
    "Error: Pack voltage too high",
    "Error: Pack voltage too low",
    "Error: IGBT desaturation",
    "Error: Out of memory",
    "Error: Software error",
    "Controller shut down by user"
  };
/******************************************
 * Function: Ctor
 *
 * Parameters:
 * 	Motor * data - pointer to a motor data object
 * 		for storage purposes
 * 	const char * ip_address - String containing the IP address for boost asio
 * 	int port - Port number the Soliton Motor Controller is communicating on
 ******************************************/
SolitonReader::SolitonReader(Motor * data):
	iEMController(data),
	current_write(0), 
	debug((uint16_t *)buf)
{
	
	log = fopen ("logger.txt", "w");
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE;
	rv = getaddrinfo(NULL, MYPORT, &hints, &servinfo);
	
	// loop through all the results and bind to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("listener: socket");
			continue;
		}
		
		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("listener: bind");
			continue;
		}
		break;
	}
	freeaddrinfo(servinfo);
	m_update = new boost::thread(boost::bind(&SolitonReader::UpdateLoop,this));
}

SolitonReader::~SolitonReader()
{
	m_update->interrupt();
	m_update->join();
	delete m_update;
	m_update = 0;
}

void SolitonReader::Update()
{
	this->Parse();
}
/*************************************
 * Function: UpdateLoop()
 *
 * Purpose: Gets the most recent data sent out by
 * 	the Soliton controller
 *************************************/
void SolitonReader::UpdateLoop()
{
	while(1)
	{
		boost::this_thread::disable_interruption di;
		while(buffer[current_write].lock.try_lock())
			current_write = current_write % 5 ? current_write + 1 : 0;
		buffer[current_write].oldmstic = 0xffff;
		numbytes = recvfrom(sockfd, buffer[current_write].buffer, MAXBUFLEN-1 , 0, NULL, NULL);
		buffer[current_write].lock.unlock();

		boost::this_thread::restore_interruption ri(di);
		boost::this_thread::sleep(boost::posix_time::microseconds(100000));
	}
}

/**********************************************
 * Function: Parse()
 *
 * Purpose: Parse out the most recent data and push it
 * 	into its appropriate containers
 **********************************************/
void SolitonReader::Parse()
{
	int currentRead = current_write;
	currentRead = currentRead -1 > 0 ? currentRead -1:0;
	SolitonBuffer locBuff;

	buffer[currentRead].lock.lock();
	strcpy(locBuff.buffer,buffer[currentRead].buffer);
	locBuff.oldmstic = buffer[currentRead].oldmstic;
	buffer[currentRead].lock.unlock();
	
	if (numbytes && !locBuff.buffer[0])
	{
		if (locBuff.oldmstic != debug[LOG_MSTICS] / 200)
		{
			locBuff.oldmstic = debug[LOG_MSTICS] / 200;
			printf ("\r%2.1d:%2.2d:%2.2d - CPU:%3.1d%% Thr:%3.1dA "
				"I:%3.1dA D:%3.1d.%1.1d Pack:%3.1dV "
				"T:%3.1d.%1.1d RPM:%4.1d ",
				debug[LOG_MINTICS] / 60,
				debug[LOG_MINTICS] % 60,
				debug[LOG_MSTICS] / 1000,
				debug[LOG_CPULOAD] >> 7,
				debug[LOG_THROTTLE],
				debug[LOG_CURRENT],
				debug[LOG_PWM] / 10,
				debug[LOG_PWM] % 10,
				debug[LOG_PACKV],
				((int16_t) debug[LOG_TEMP])/10,
				abs((int16_t) debug[LOG_TEMP])%10,
				debug[LOG_RPM]);

			fflush (stdout);
		}
	
		fprintf (log, "%d %f %d %d %f %d %f %d %f %f %f %f %d "
			"%s%s%s%s%s%s%s%s%s%s%s\n",
			debug[LOG_MSTICS] +
			debug[LOG_MINTICS] * 60000,
			debug[LOG_CPULOAD] / 128.0,
			debug[LOG_THROTTLE],

			debug[LOG_CURRENT],

			debug[LOG_PWM] / 10.0,

			debug[LOG_PACKV],
			((int16_t) debug[LOG_TEMP])/10.0,
			debug[LOG_RPM],
			debug[LOG_INPUT1] * 0.000080645,
			debug[LOG_INPUT2] * 0.000080645,
			debug[LOG_INPUT3] * 0.000080645,
			debug[LOG_AUXV] * 0.00025939941 + 1.0,
			debug[LOG_MODE], mode[debug[LOG_MODE] & 0x1f],
			
			debug[LOG_MODE] & LIMIT_HIMOTORV ? ", High motor volt" : "",
			debug[LOG_MODE] & LIMIT_HIMOTORP ? ", High motor power" : "",
			debug[LOG_MODE] & LIMIT_MTEMP ? ", Motor temp high" : "",
			debug[LOG_MODE] & LIMIT_OVERREV ? ", RPM high" : "",

			debug[LOG_MODE] & LIMIT_LOWPACKV ? ", Low pack volt" : "",
			debug[LOG_MODE] & LIMIT_HIPACKC ? ", High pack current" : "",
			debug[LOG_MODE] & LIMIT_HVC ?
			", High pack volt 900 Amp current" : "",
			debug[LOG_MODE] & LIMIT_CTEMP ?
			", Controller temp high" : "",
			
			debug[LOG_MODE] & LIMIT_SLEWRATE ? ", Slewrate active" : "",
			debug[LOG_MODE] & LIMIT_BLOCKED ? ", Throttle blocked" : "");
		
		GetMotorData().SetRpm((double)debug[LOG_RPM]);
		GetMotorData().SetTemp(((double) debug[LOG_TEMP])/10.0);
		static int stuff = 0;
		stuff += 10;
		stuff %= 200;
		GetMotorData().SetSpeed((double)stuff);
		
		
	}
	else
	{
		printf("\r                                                                             \r");
		if (numbytes)
		{
			locBuff.buffer[numbytes] = '\0';
			while (strlen (locBuff.buffer) && locBuff.buffer[strlen (locBuff.buffer) - 1] < ' ')
			locBuff.buffer[strlen (locBuff.buffer) - 1] = '\0';
			printf ("%s\n", locBuff.buffer);
		}
		else
		{
			printf ("Empty message!\n");
		}
	}
}