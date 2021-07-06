// MySQLInterface


#ifndef __MYSQL_INTERFACE_H__  
#define __MYSQL_INTERFACE_H__  

#include <string>  
#include <vector>  

#include <winsock.h> 
#include "mysql.h"


#pragma comment(lib, "ws2_32.lib")  
#pragma comment(lib, "libmysql.lib")

#define ERROR_QUERY_FAIL -1 


// Define MySQL Connection Info
typedef struct
{
	char* server;
	char* user;
	char* password;
	char* database;
	int port;
}MySQLConInfo;

class MySQLInterface
{
public:
	MySQLInterface();
	virtual ~MySQLInterface();

	void SetMySQLConInfo(char* server, char* username, char* password, char* database, int port);// Set Connection Info
	bool Open();  // Open Connection
	void Close(); // Close Connection

	// Select into data
	bool Select(const std::string& Querystr, std::vector<std::vector<std::string> >& data);	     
	bool Query(const std::string& Querystr);     // Other operations
	int GetInsertID(const std::string& Querystr);// Insert and then get the ID, assuming auto incrementation
	void ErrorIntoMySQL();		 // Error message

public:
	int ErrorNum;				 // Error code  
	const char* ErrorInfo;       // Error Info

private:
	MySQLConInfo MysqlConInfo;	 // Connection Info
	MYSQL MysqlInstance;		 // MySQL Instance
	MYSQL_RES* Result;			 // Result set
};

#endif




//reference link£ºhttps ://blog.csdn.net/daoming1112/article/details/54710743
