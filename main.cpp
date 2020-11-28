//Main System Launcher for the LMS

#include <iostream>
#include <fstream>

#include "Display.h"
#include "UserAuth.h"
#include "Database.h"

using namespace std;

//Setup
void startup();
void start();

//UI
void gui();
void changePassword();

int current = -1; //Index of current student in the database, if successful this value is > 0

//Runner
int main() {
	startup();
	start();
	return 0;
}

void printBooks() {
	fstream ya("data\\ya.txt");
	for (Book b : Database::getBooks()) {
		b << cout << endl;
		b << ya << endl;
	}
	cout << "\n\n\n\n";
	ya << "\n\n\n\n";
	for (Copy c : Database::getCopies()) {
		c << cout << endl;
		c << ya << endl;
	}
	cout << "\n\n\n\n";
	ya << "\n\n\n\n";
	ya.close();
}

//Load into RAM the book/student data upon failure, the system aborts
void startup() {
	if (!Database::loadBooks())
		exit(-3);
	printBooks();
	if (!Database::loadStudents())
		exit(-4);
	exit(4173);
}

//Welcome and Login Menu
void start() {
	Display::welcome();
	int choice;
	Display::clrscr();
	cout << "Choice: ";
	cin >> choice;
	if (choice == 0) {
		while(!UserAuthentication::signup(cin)){
			Display::clrscr();
			Display::border();
			cout << "This user already exists! Please choose a different username." << endl << endl;
			Display::border();
		}
		Display::clrscr();
		start();
	}
	else {
		Display::clrscr();
		while ((current = UserAuthentication::login(cin))<0) { //Attempt Login, Repeats until login is successful, result is stored in 'current'
			cout << endl;
			Display::border();
			cerr << "Invalid Username and/or Password. Please try again." << endl << endl;
			Display::border();
		}
		gui(); //Load successful login menu
	}
}

void gui() {
	Display::clrscr();
	Display::border();
	cout << "You have successfully logged into the Library Management System." << endl;
	int choice = 0;
	Display::menu();
	Display::clrscr();
	cout << "Choice: ";
	cin >> choice;
	while (choice > 0) {
		Display::border();
		switch (choice) {
		case 1: //Search for Books
			cout << "To be implemeneted" << endl;
			break;
		case 2: //Borrow Books - Submission 1
			//Database::getReaders().at(current).borrowBooks(cin);
			break;
		case 3: //Return Books - Submission 1
			//Database::getReaders().at(current).returnBooks(cin);
			break;
		case 4: //Reserve Books
			cout << "To be implemeneted" << endl;
			break;
		case 5: //Cancel Reservations
			cout << "To be implemeneted" << endl;
			break;
		case 6: //About Me
			Database::getReaders().at(current) << cout;
			break;
		case 7: //Change Password
			changePassword();
			Database::save();
			break;
		case 8: //Debug Command, Prints Book Database and Student Database
			cout << "========= Books =========" << endl;
			for (Book b : Database::getBooks())
				b << cout << endl;
			cout << "========= Students =========" << endl;
			for (Reader s : Database::getReaders())
				s << cout << endl;
			break;
		default: //Invalid Input
			cout << "Invalid selection. Please enter a valid ID." << endl;
		}
		Display::menu();
		Display::clrscr();
		cout << "Choice: ";
		cin >> choice;
		cout << endl << endl;
	}
	Display::clrscr();
	Display::clrscr();
	Display::border();
	Database::save(); //write database data back to files
	cout << "You have successfully logged out of the Library Management System. Have a great day." << endl << endl;
	start();
}

//Option 7 - Change Current User's Password
void changePassword() {
	string pw;
	cout << "Enter your current password: ";
	cin >> pw;
	if (pw == Database::getReaders().at(current).getPassword()) {
		cout << "Enter your new desired password: ";
		cin >> pw;
		for (Reader s : Database::getReaders()) //change in the database as well as the current session
			if (s == Database::getReaders().at(current))
				Database::getReaders().at(current).setPassword(pw);
		cout << "Change successful." << endl;
	}
	else
		cout << "Change unsuccessful. Failed to verify user information." << endl;
}