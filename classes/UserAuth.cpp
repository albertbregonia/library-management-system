#include "UserAuth.h"
#include "Database.h"

using namespace std;

//Registers a new user into the database
bool UserAuthentication::signup(istream &in) {
	string user, pw;
	cout << "Please enter your desired username: ";
	in >> user;
	for (Reader r : Database::getReaders()) //Unique usernames are required
		if (r.getUsername() == user)
			return false;
	cout << "Please enter your desired password: ";
	in >> pw;
	Reader r = Reader();
	r.setUsername(user);
	r.setPassword(pw);
	Database::getReaders().push_back(r);  //change in the database as well as the current session
	Database::save(); //write out to file
	return true;
}

//Attempt Login
int UserAuthentication::login(istream &in, bool type) {
	string user, pw;
	cout << "Please enter your username: ";
	in >> user;
	cout << "Please enter your password: ";
	in >> pw;
	if (type) {
		for (int i = 0; i < Database::getReaders().size(); i++)
			if (Database::getReaders().at(i).getUsername() == user && Database::getReaders().at(i).getPassword() == pw)
				return i; //returns the index of the student in the database
	}
	else
		for (int i = 0; i < Database::getAdmins().size(); i++)
			if (Database::getAdmins().at(i).getUsername() == user && Database::getAdmins().at(i).getPassword() == pw)
				return i; //returns the index of the student in the database
	return -1; //returns -1 upon failure to find a student of those credentials
}

