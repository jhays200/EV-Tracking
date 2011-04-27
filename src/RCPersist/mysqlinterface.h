#ifndef MYSQL_INTERFACE
#define MYSQL_INTERFACE
#include <WinSock.h>
#include <mysql.h>
#include <string>
using std::string;

class iDatabase
{
public:
	//virtual bool Insert(const char * insert)=0;
	virtual bool Query(const char *)=0;
	virtual  string Fetch()=0;
	virtual void Disconnect()=0;
private:
	virtual MYSQL * Connect() = 0;	
};
#endif