#include "User.h"
#include <iostream>

//Constructors
User::User() :
	username("none"),
	password("none")
{}

User::User(string username, string password) :
	username(username),
	password(password)
{}

//Accessors
string User::getUsername() { return username; }
string User::getPassword() { return password; }

//Mutators
void User::setUsername(string username) { this->username = username; }
void User::setPassword(string password) { this->password = password; }

//Overloaded Operators
ostream& User::operator<<(ostream& out) {
	if (&out == &cout) {
		out << "Username: " << username << endl;
		out << "Password: " << password << endl;
	}
	else {
		out << endl << username << endl;
		out << password << endl;
		out << "----------------";
	}
	return out;
}

istream& User::operator>>(istream& in) {
	string line;
	if (!in.eof())
		for (int i = 0; i < 3; i++) {
			getline(in, line);
			if (line.empty())
				break;
			switch (i) {
			case 0:
				username = line;
				break;
			case 1:
				password = line;
				break;
			case 2: //line delimiter
				break;
			}
		}
	return in;
}