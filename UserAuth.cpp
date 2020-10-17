//Albert Bregonia 10/16

#include <iostream>
#include <istream>

#include "Display.h"
#include "UserAuth.h"
#include "Student.h"
#include "Startup.h"

using namespace std;

//Registers a new user into the database
bool UserAuthentication::signup(istream &in) {
	string user, pw;
	cout << "Please enter your desired username: ";
	in >> user;
	cout << "Please enter your desired password: ";
	in >> pw;
	//****TO DO: Update System****//
	return true;
}

//Attempt Login
bool UserAuthentication::login(istream &in) {
	string user, pw;
	cout << "Please enter your username: ";
	in >> user;
	cout << "Please enter your password: ";
	in >> pw;
	return success(user, pw);
}

//Check for Valid Username and Password
bool UserAuthentication::success(string& username, string& password) {
	for (Student s : Startup::getStudents())
		if (s.getUsername() == username && s.getPassword() == password)
			return true;
	return false;
}

