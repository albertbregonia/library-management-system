#pragma once
#include <string>
using namespace std;

class User
{
private:
	string username;
	string password;
public:
	//Constructors
	User();
	User(string username, string password);
	//Accessors
	string getUsername();
	string getPassword();
	//Mutators
	void setUsername(string username);
	void setPassword(string password);

	friend ostream& operator<<(ostream& out, User& u);
	friend istream& operator>>(istream& in, User& u);
	bool operator==(User& u);
};

