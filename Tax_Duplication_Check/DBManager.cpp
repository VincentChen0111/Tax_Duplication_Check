#include "DBManager.h" 
#include <iostream>
using namespace std;

int pnf(int n) {
	int respond;
	switch (n) {
	case 0:
		cout << "Welcome to cs348 mart database system.\nPlease choose an option:" << endl;
		cout << "1. Sign up\n"
			<< "2. Log in\n"
			<< "3. Log in as admin\n"
			<< "4. Continue as temporary user\n"
			<< "0. Quit" << endl;
		break;

	case 1:
		cout << "\nYou are in database as admin" << ".\nPlease choose an operation:" << endl;
		cout << "1. Display items\n"
			<< "2. add items \n"
			<< "3. Update items \n"
			<< "4. Delete items\n"
			<< "5. Modify categories\n"
			<< "6. Modify on sale items\n"
			<< "0. Quit" << endl;
		break;

	case 2:
		cout << "\nYou are in database" << ".\nPlease choose an operation:" << endl;
		cout << "1. Display items\n"
			<< "2. Search items\n"
			<< "3. Add item to cart\n"
			<< "4. Go to cart\n"
			<< "5. Check out\n"
			<< "0. Quit" << endl;
		break;

	case 3:
		cout << "\nYou are in the search menu" << ".\nPlease choose an operation:" << endl;
		cout << "1. Search by name\n"
			<< "2. Search by category\n"
			<< "3. return to main menu\n" << endl;
		break;
	default:
		return -1;
	}

	cin >> respond;
	cin.clear();
	cin.ignore();
	return respond;
}

DBManager::DBManager(MySQLInterface* MI) : MI(MI) {};

void DBManager::display() {
	for (unsigned int i = 0; i < data.size(); ++i) {
		for (unsigned int j = 0; j < data[0].size(); ++j)
			cout << data[i][j] << "\t\t\t";
		cout << endl;
	}
}

void DBManager::errSelect(string sqlstr) {
	if (!MI->Select(sqlstr, data))
		cout << MI->ErrorNum << " : " << MI->ErrorInfo << endl;
}

void DBManager::errQuery(string sqlstr) {
	if (!MI->Query(sqlstr))
		cout << MI->ErrorNum << " : " << MI->ErrorInfo << endl;
}

void DBManager::clean() {
	data.clear();
}

UsrCtrl::UsrCtrl(MySQLInterface* UsrCt) : DBManager::DBManager(UsrCt) {};

bool UsrCtrl::validate(int id, string pw) {
	errSelect("Select password from RegisteredUsers where uid=" + to_string(id) + ";");
	if (data.empty()) return false;
	if (data.at(0).at(0) == pw) return true;
	return false;
}

bool UsrCtrl::reg(int id, std::string name, std::string pw) {
	errSelect("Select * from Users where uid=" + to_string(id) + ";");
	if (!data.empty()) return false;
	errQuery(R"(INSERT INTO Users
VALUES 
   ()" + to_string(id) + ")");
	errQuery(R"(INSERT INTO RegisteredUsers
VALUES 
   ()" + to_string(id) + ",'" + name + "','" + pw + "',0)" );
	return true;
}