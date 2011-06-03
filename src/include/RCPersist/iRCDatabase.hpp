#pragma once
#include <string>
using namespace std;
#include <mysql/mysql.h>
#include <mysql/my_global.h>


class iRCDatabase
{
public:
	iRCDatabase(const char * host, const char * user, const char * password, const char * db);
	~iRCDatabase();
	void Query(const char * q);
private:
// 	std::string m_host;
// 	std::string m_user;
// 	std::string m_password;
// 	std::string m_db;
	MYSQL mysql;
};