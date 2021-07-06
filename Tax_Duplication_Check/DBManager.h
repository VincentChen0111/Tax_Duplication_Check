
#ifndef __DB_MANAGER_H__  
#define __DB_MANAGER_H__   

#include "sql_api.h"

//prompt the menu then fetch the choice from the user
//	menu 0: welcome
//	menu 1: admin main
//	menu 2: customer main
int pnf(int n);


class DBManager {
protected:
	MySQLInterface* MI;
	std::vector<std::vector<std::string>> data;
public:
	DBManager(MySQLInterface* MI);
	void display();
	void errSelect(std::string sqlstr);
	void errQuery(std::string sqlstr);
	void clean();

};

class UsrCtrl : public DBManager{

public:
	UsrCtrl(MySQLInterface* UsrCt);//this has to be a valid mysql connection that has access to user table
	//validate the given user name and password
	bool validate(int id, std::string pw);
	//create a new registerd user
	bool reg(int id, std::string name, std::string pw);
};

class AdminDBM : public DBManager {

};

class CustDBM : public DBManager {

};


#endif