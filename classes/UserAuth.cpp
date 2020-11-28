#include <iostream>
#include <istream>

#include "Display.h"
#include "UserAuth.h"
#include "Student.h"
#include "Database.h"

using namespace std;

//Registers a new user into the database
bool UserAuthentication::signup(istream &in) {
	string user, pw;
	cout << "Please enter your desired username: ";
	in >> user;
	for (Student s : Database::getReaders()) //Unique usernames are required
		if (s.getUsername() == user)
			return false;
	cout << "Please enter your desired password: ";
	in >> pw;
	Student s = Student();
	s.setUsername(user);
	s.setPassword(pw);
	Database::getReaders().push_back(s);  //change in the database as well as the current session
	Database::save(); //write out to file
	return true;
}

//Attempt Login
int UserAuthentication::login(istream &in) {
	string user, pw;
	cout << "Please enter your username: ";
	in >> user;
	cout << "Please enter your password: ";
	in >> pw;
	for (int i=0; i<Database::getReaders().size(); i++)
		if (Database::getReaders().at(i).getUsername() == user && Database::getReaders().at(i).getPassword() == pw)
			return i; //returns the index of the student in the database
	return -1; //returns -1 upon failure to find a student of those credentials
}

