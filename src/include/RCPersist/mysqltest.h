#ifndef MYSQL_TEST
#define MYSQL_TEST
#include "mysqlinterface.h"

class RCDatabaseTest : public iDatabase
{
public:
	RCDatabaseTest(const char * , const char *, const char *,
		       const char * = 0);
	
	bool Query(const char *);
	//bool Insert(const char * insert);
	
	string Fetch();
	
	void Disconnect();
	
private:
	virtual MYSQL * Connect();
	
	bool connected;
	
	string m_server;
	string m_user;
	string m_password;
	string m_database;
	
	MYSQL * m_connection;
	MYSQL_RES * m_result;
	MYSQL_ROW m_row;
};
#endif