// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "sql_api.h"
#include "DBManager.h"
#include <iostream>
using namespace std;




int main(int argc, char* argv[]){
	MySQLInterface usrCtrl;
	MySQLInterface MySQLInterface;
	char hst[] = "cs348-project.c56bjewfihhr.us-east-2.rds.amazonaws.com"; //host name
	char db[] = "DB1"; //database
	char uc[] = "UsrCtrl"; //the user control
	char uc_pw[] = "123456"; //the password for user control admin
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
	DBManager dbm(&MySQLInterface);

	//login section

	choice = pnf(0);
	int id;
	string pw, name;
	bool in;

	switch (choice) {
	case 1:
		cout << "Enter your id, name and password." << endl;
		cin >> id;
		cin >> name >> pw;
		cin.clear();
		cin.ignore();
		usrc.reg(id, name, pw);
		pwd = (char*)"123456789";
		usr = (char*)"customer";
		in = true;
		break;
	case 2:
		cout << "Enter your id and password." << endl;
		cin >> id;
		cin >> pw;
		cin.clear();
		cin.ignore();
		in = usrc.validate(id, pw);
		pwd = (char*)"123456789";
		usr = (char*)"customer";
		break;
	case 3:
		cout << "Enter the password for admin account" << endl;
		cin >> pw;
		cin.clear();
		cin.ignore();
		in = (pw == admin_pw);
		pwd = (char*)"123456";
		usr = (char*)"admin";
		break;
	case 4:
		cout << "not supported" << endl;
		exit(1);
	case 0:
		exit(0);
	default:
		exit(1);
	}
	
	if (!in) {
		cout << "invalid id or password" << endl;
		exit(1);
	}

	
	MySQLInterface.SetMySQLConInfo(hst, usr, pwd, db, 3306);

	if (!MySQLInterface.Open()){
		cout << MySQLInterface.ErrorNum << " : " << MySQLInterface.ErrorInfo << endl;
		exit(1);
	}

	//admin account
	if(choice == 3){
		choice = 0;
		while (true) {
			choice = pnf(1);

			if (choice == 0) break;

			string sqlstr, qname;
			string id, name, price, stock;


			switch (choice) {
			case 1:
				// simple query

				sqlstr = "SELECT * FROM `DB1`.`Items`;";
				dbm.errSelect(sqlstr);
				dbm.display();
				dbm.clean();
				break;

			case 2:

				// simple query
				cout << "\nPlease enter item id, name, price, stock:" << endl;
				cin >> id >> name >> price >> stock;
				cin.clear();
				cin.ignore();
				sqlstr = R"(INSERT INTO Items
VALUES 
   (')" + id + "','" + name + "','" + price + "','" + stock + "')";
				dbm.errQuery(sqlstr);

				break;
			case 0:
				break;
			default:
				cout << "not supported" << endl;
				break;
			}

			choice = 0;
		}
	}

	//customer account
	else {
		choice = 0;
		while (true) {
			choice = pnf(2);

			if (choice == 0) break;

			int c;
			string sqlstr, qname;
			string id, name, price, stock;


			switch (choice) {
			case 1:
				// simple query

				sqlstr = "SELECT * FROM `DB1`.`Items`;";
				dbm.errSelect(sqlstr);
				dbm.display();
				dbm.clean();
				break;

			case 2:

				//search
				c = pnf(3);
				switch (c) {
				case 1:
					//search by name
					cout << "Enter the name of search: " << endl;
					cin >> qname;
					cout << endl;
					sqlstr = "select * from Items where name like '%" + qname + "%'";
					dbm.errSelect(sqlstr);
					dbm.display();
					dbm.clean();
					break;
				case 2: 
					//search by category
					cout << "Enter the name of the category: " << endl;
					cin >> qname;
					cout << endl;
					sqlstr = "select * from Items inner join ( select iid from IsMemberOf inner join ( select cid from Categories where Categories.cname = '" + qname + "' ) as query_cid on IsMemberOf.cid = query_cid.cid) as query_table on Items.iid = query_table.iid";
					dbm.errSelect(sqlstr);
					dbm.display();
					dbm.clean();
					break;
				default:
					break;
				}

				break;

			
			default:
				cout << "not supported" << endl;
				break;
			}

			choice = 0;
		}
	}


	MySQLInterface.Close();
	usrCtrl.Close();



	return 0;

}