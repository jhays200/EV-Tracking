#include <iRCDatabase.hpp>

iRCDatabase::iRCDatabase(const char * host, const char * user, const char * password, const char * db)
{
// 	this->m_host = host;
// 	this->m_user = user;
// 	this->m_password = password;
// 	this->m_db = db;
	
	mysql_init(&mysql);
	mysql_real_connect(&mysql, host,user,
					   password,db,0,NULL,0);
}

iRCDatabase::~iRCDatabase()
{
    mysql_close(&mysql);
}

void iRCDatabase::Query(const char * q)
{
	mysql_query(&mysql, q);
}