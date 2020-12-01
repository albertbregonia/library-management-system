#include "UserAuth.h"
#include "Database.h"
#include "Teacher.h"
#include <conio.h>

using namespace std;

//Registers a new user into the database
bool UserAuthentication::signup(istream &in) {
	cout << "What type will this user be: " << endl;
	cout << "\t0 - Student" << endl;
	cout << "\t1 - Teacher" << endl;
	cout << "\t2 - Librarian/Administrator" << endl;
	cout << endl << endl << "Choice: ";
	int choice;
	in >> choice;
	string user, pw;
	cout << "Please enter the desired username (Capitalization is ignored): ";
	in >> user;
	user = Database::toLower(user);
	if (Database::getAdminByUsername(user) < 0 && Database::getReaderByUsername(user) < 0) {//Unique usernames are required
		cout << "Please enter the desired password: ";
		in >> pw;
		Teacher t;
		Student s;
		Librarian l;
		switch (choice) {
		case 1:
			t.setUsername(user);
			t.setPassword(pw);
			Database::getReaders().push_back(t);
			break;
		case 2:
			l.setUsername(user);
			l.setPassword(pw);
			Database::getAdmins().push_back(l);
			break;
		default: //by default, users are students
			s.setUsername(user);
			s.setPassword(pw);
			Database::getReaders().insert(Database::getReaders().begin() + Database::getPartitioner() + 1, s);
			Database::setPartitioner(Database::getPartitioner() + 1); //shift the partitioner over as a student was just added
			break;
		}
		Database::save(); //write out to file
		return true;
	}
	return false;
}

//Attempt Login
int UserAuthentication::login(istream &in, bool& type) {
	string user, pw;
	cout << "Please enter your username: ";
	in >> user;
	cout << "Please enter your password: ";
	char c;
	int ctr = 0; //pos for backspace in password mask
	while ((c=_getch()) != '\r'){ //using <conio.h> and C functions, treat 'pw' like a vector and put '*' per character
		if (c > 32 && c < 128) { //if alphabet
			pw.push_back(c); //check until 'c' is the return key or '\r' (basically when you press enter)
			cout << "*";
			ctr++;
		}
		else if (c == 8 && ctr > 0) { //backspace
			pw.erase(pw.end()-1);
			cout << "\b \b";
			ctr--;
		}
	}
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

