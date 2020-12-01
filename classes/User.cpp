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
ostream& operator<<(ostream& out, User& u) {
	if (&out == &cout) {
		out << "Username: " << u.username << endl;
		out << "Password: " << u.password << endl;
	}
	else {
		out << endl << u.username << endl;
		out << u.password << endl;
		out << "----------------";
	}
	return out;
}

istream& operator>>(istream& in, User& u) {
	string line;
	if (!in.eof())
		for (int i = 0; i < 3; i++) {
			getline(in, line);
			if (line.empty())
				break;
			switch (i) {
			case 0:
				u.username = line;
				break;
			case 1:
				u.password = line;
				break;
			case 2: //line delimiter
				break;
			}
		}
	return in;
}