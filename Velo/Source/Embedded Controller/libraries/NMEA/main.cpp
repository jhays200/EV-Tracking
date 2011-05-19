#include <iostream>
using std::cin;
using std::cout;

#include "NMEA.h"

void main()
{
	NMEA* Parser = new NMEA;
	char InputString[] = "$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47\r\n";

	for(int i = 0; InputString[i]; ++i)
		Parser->Parse(InputString[i]);

	delete Parser;
	_CrtDumpMemoryLeaks();
}