#ifndef SERIAL_H
#define SERIAL_H
/*
 * Class: EvSerialIO
 * Author: Jeffrey Conradt
 * Date Created: 1/12/2011
 * Last Modified: 1/12/2011
 * 	By: Jeffrey Conradt
 * 
 * Tested: No
 * 
 * Summary: 
 * 	The EvSerialIO class is a simple utility class that is meant to read and write a single 
 * 	Serial IO file (ttyS0, ttyS1, ttyUSB0, etc...), and handle all options required with it.
 * 	NOTE: Once you set your options once, do not change them. Your setting DO NOT CHANGE, once established.
 * 	
 * 
 * Public Methods:
 * 	
 * 	EvSerialIO(char * file, int open_options [optional]) void -- 
 * 		Upon creation of the SerialIO class, you must specify a file to communicate with, as well as any options you may wish to apply as well.
 * 		The default options open the file so that you are *not* the controlling terminal, which is desireable,
 * 		you have read / write access, and that the process does not care whether or not you have a connection.
 * 		
 * 	~EvSerialIO() void -- Just a destructor, move along, nothing to see here.
 * 
 * 	--Each of these you need to set manually--
 * 	void SetReadOptions(bool options);
 * 	
 * 	void SetBaud(int baud, int options = TCSANOW);
 * 
 * 	void SetParityChecking(Parity check); 
 * 
 * 	void SetHardwareFlowControl(bool control);
 * 
 * 	void SetLocal(Local options, int other = 0);
 * 
 * 	void SetInputOptions(int options);
 * 
 * 	void SetSoftwareFlowControl(bool control);
 * 
 * 	oid SetOutputOptions(int options, int other = 0);
 * 
 * 
 * Private Members:
 * 	int fd;				--File descriptor
 *	struct termios options;		--Option structure
 */


/*Explanation on serial programming in Unix can be found here: http://digilander.libero.it/robang/rubrica/serial.htm*/

//REFERENCE

/* 
Baud Rates 
CBAUD	Bit mask for baud rate
B0	0 baud (drop DTR)
B50	50 baud
B75	75 baud
B110	110 baud
B134	134.5 baud
B150	150 baud
B200	200 baud
B300	300 baud
B600	600 baud
B1200	1200 baud
B1800	1800 baud
B2400	2400 baud
B4800	4800 baud
B9600	9600 baud
B19200	19200 baud
B38400	38400 baud
B57600	57,600 baud
B76800	76,800 baud
B115200	115,200 baud
EXTA	External rate clock
EXTB	External rate clock
CSIZE	Bit mask for data bits
CS5	5 data bits
CS6	6 data bits
CS7	7 data bits
CS8	8 data bits
CSTOPB	2 stop bits (1 otherwise)
CREAD	Enable receiver
PARENB	Enable parity bit
PARODD	Use odd parity instead of even
HUPCL	Hangup (drop DTR) on last close
CLOCAL	Local line - do not change "owner" of port
LOBLK	Block job control output
CNEW_RTSCTS
CRTSCTS	Enable hardware flow control (not supported on all platforms)
*/

/* 
Input Options:
NPCK	Enable parity check
IGNPAR	Ignore parity errors
PARMRK	Mark parity errors
ISTRIP	Strip parity bits
IXON	Enable software flow control (outgoing)
IXOFF	Enable software flow control (incoming)
IXANY	Allow any character to start flow again
IGNBRK	Ignore break condition
BRKINT	Send a SIGINT when a break condition is detected
INLCR	Map NL to CR
IGNCR	Ignore CR
ICRNL	Map CR to NL
IUCLC	Map uppercase to lowercase
IMAXBEL	Echo BEL on input line too long
*/

/*
Output Options:
OPOST	Postprocess output (not set = raw output)
OLCUC	Map lowercase to uppercase
ONLCR	Map NL to CR-NL
OCRNL	Map CR to NL
NOCR	No CR output at column 0
ONLRET	NL performs CR function
OFILL	Use fill characters for delay
OFDEL	Fill character is DEL
NLDLY	Mask for delay time needed between lines
NL0	No delay for NLs
NL1	Delay further output after newline for 100 milliseconds
CRDLY	Mask for delay time needed to return carriage to left column
CR0	No delay for CRs
CR1	Delay after CRs depending on current column position
CR2	Delay 100 milliseconds after sending CRs
CR3	Delay 150 milliseconds after sending CRs
TABDLY	Mask for delay time needed after TABs
TAB0	No delay for TABs
TAB1	Delay after TABs depending on current column position
TAB2	Delay 100 milliseconds after sending TABs
TAB3	Expand TAB characters to spaces
BSDLY	Mask for delay time needed after BSs
BS0	No delay for BSs
BS1	Delay 50 milliseconds after sending BSs
VTDLY	Mask for delay time needed after VTs
VT0	No delay for VTs
VT1	Delay 2 seconds after sending VTs
FFDLY	Mask for delay time needed after FFs
FF0	No delay for FFs
FF1	Delay 2 seconds after sending FFs
*/


#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

//One of these will be defined, I don't feel like dealing with both...
#ifndef CNEW_RTSCTS 
#define CNEW_RTSCTS CRTSCTS
#endif
#ifndef CRTSCTS
#define CRTSCTS CNEW_RTSCTS
#endif

//User defined identifiers
#define NO_PARITY 0
#define EVEN_PARITY 1
#define ODD_PARITY 2
#define SPACE_PARITY 3

#define OTHER -1
#define RAW 0
#define PROCESSED 1
#define CANONICAL 2

//Aaaannnnddd off we go (finally)
class EvSerialIO
{
public:
  EvSerialIO(const char * file, int open_options = O_RDWR | O_NOCTTY | O_NDELAY );
  
  //Just a destructor...
  ~EvSerialIO();
  
  //--Each of these you need to set manually--
  
  //Set ReadOptions (blocking/non-blocking, true/false)...
  void SetReadOptions(bool options);
  
  //Set the baud rate (detailed below)...
  void SetBaud(int baud, int options = TCSANOW);
  
  //Set parity checking (NO_PARITY, EVEN_PARITY, ODD_PARITY, SPACE_PARITY)...
  void SetParityChecking(int check);
  
  //Set hardware flow control (on/off, true/false)...
  //NOTE: Not available on all systems.
  void SetHardwareFlowControl(bool control);
  
  //Set Local Options (usually canonical or raw)...
  //If you use OTHER, you must pass in the options you want as "other"
  void SetLocal(int local, int other = 0);
  
  //Set Input Options (designate yourself, options displayed below)...
  void SetInputOptions(int option);
  
  //Set Software flow control (on/off, true/false)...
  void SetSoftwareFlowControl(bool control);
  
  //Set Output Options...
  //NOTE: You should only need RAW or PROCESSED input. If you choose to 
  //	use another form of input ,then you *must* set 'other' to be the desired options.
  void SetOutputOptions(int option, int other = 0);
  
  void Write(const char *, size_t);
  void Read(char * buffer, size_t size);
private:
  int fd;
  struct termios options;
};

#endif