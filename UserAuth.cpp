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
bool UserAuthentication::login(istream &in, Student& current) {
	string user, pw;
	cout << "Please enter your username: ";
	in >> user;
	cout << "Please enter your password: ";
	in >> pw;
	for (Student student : Startup::getStudents())
		if (student.getUsername() == user && student.getPassword() == pw) {
			current = student;
			return true;
		}
	return false;
}

