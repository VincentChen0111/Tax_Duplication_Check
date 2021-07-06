// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "sql_api.h"
#include "DBManager.h"
#include <iostream>
using namespace std;




int main(int argc, char* argv[]){
	MySQLInterface usrCtrl;
	MySQLInterface MySQLInterface;
	char hst[] = "taxdupcheck.c56bjewfihhr.us-east-2.rds.amazonaws.com"; //host name
	char db[] = "code"; //database
	char uc[] = "admin"; //the user control
	char uc_pw[] = "123456789"; //the password for user control admin
	char admin[] = "admin";
	char admin_pw[] = "123456";
	char customer[] = "customer";
	char customer_pw[] = "123456789";
	char* usr = new char[24]; //user
	char* pwd = new char[10]; //password
	int choice;
	usrCtrl.SetMySQLConInfo(hst, uc, uc_pw, db, 3306);
	if (!usrCtrl.Open()) {
		cout << usrCtrl.ErrorNum << " : " << usrCtrl.ErrorInfo << endl;
		exit(1);
	}
	UsrCtrl usrc(&usrCtrl);
	bool nq = true;

	string code;
	while(nq){
		cout << "To check for duplication, please enter the text you get after scanning the QR-code:" << endl;
		cin >> code;
		cin.clear();
		cin.ignore();

		bool ndup = usrc.validate(1, code);

		if (ndup) {
			cout << "Not duplicate. The text is recorded into the database." << endl;
			usrc.reg(1, code, "");
		}
		else {
			cout << "This is duplicated." << endl;
		}
		cout << "press 0 to quit, any other keys to continue." << endl;
		cin >> nq;
		cin.clear();
		cin.ignore();
	}
	usrCtrl.Close();



	return 0;

}