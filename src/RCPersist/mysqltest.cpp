#include "mysqltest.h"
#include <cstdio>
#include <iostream>
using std::cout;

RCDatabaseTest::RCDatabaseTest(const char * server, const char * user, const char * database,
                               const char * password):connected(false)
{
    m_server = server;
    m_user = user;
    m_database = database;

    if (!password)
    {
      char buff[256];
      printf("Password: ");
      gets(buff);
    }
    else
        m_password = password;

    mysql_init(&m_connection);
    while (!Connect())
    {
		 char buff[256];
		cout << "Access Denied\nPassword: " ;
			m_password = gets(buff);
        if (m_password == "quit")
            break;
    }
    Connect();
}

MYSQL * RCDatabaseTest::Connect()
{
	mysql_init(&m_connection);
    return mysql_real_connect(&m_connection,
                                     m_server.c_str(), m_user.c_str(), m_password.c_str(),
                                     m_database.c_str(), 0, NULL, 0);
}

bool RCDatabaseTest::Query(const char * query)
{
    if (mysql_query(&m_connection, query))
        return false;
    m_result = mysql_use_result(&m_connection);
    return true;
}

string RCDatabaseTest::Fetch()
{
	MYSQL_ROW row;
	unsigned int num_fields;
	unsigned int i;

	num_fields = mysql_num_fields(m_result);
		if(  row = mysql_fetch_row(m_result))
	{
	unsigned long *lengths;
	lengths = mysql_fetch_lengths(m_result);
	for(i = 0; i < num_fields; i++)
	{
		printf("[%.*s] ", (int) lengths[i],
				row[i] ? row[i] : "NULL");
	}
	return"\n";
	}
		else
			return "";
   /* char temp[256];
    m_row = mysql_fetch_row(m_result);
    if (m_row != NULL)
    {
        sprintf(temp,"%s",m_row);
        return string(temp);
    }
    else
    {
        printf("No data left from query\n");
        return string();
    }*/
}

void RCDatabaseTest::Disconnect()
{
    mysql_free_result(m_result);
    mysql_close(&m_connection);
    m_result = 0;
}

//bool RCDatabase::Insert(const char * insert)
//{
//
//}
