//Main System Launcher for the LMS

#include <iostream>
#include <fstream>

#include "Display.h"
#include "UserAuth.h"
#include "Database.h"

using namespace std;

//Debug Functions
void printBooks() { //Test Overloaded Operators
	for (Book b : Database::getBooks())
		b << cout << endl;
	cout << "\n\n\n\n";
	for (Copy c : Database::getCopies())
		c << cout << endl;
	cout << "\n\n\n\n";
}

void printAccounts() { //Test overloaded operators for accounts
	for (Reader r : Database::getReaders())
		r << cout << endl;
	for (Librarian l : Database::getAdmins())
		l << cout << endl;
}

//Setup
void startup();
void start();

//UI
void gui(bool type);
int current = -1; //Index of current student in the database, if successful this value is > 0

//Runner
int main() {
	startup();
	start();
	return 0;
}

//Load into RAM the book/student data upon failure, the system aborts
void startup() {
	if (!Database::loadBooks())
		exit(-3);
	else if (!Database::loadAccounts())
		exit(-4);
}

//Welcome and Login Menu
void start() {
	bool type; // true for student/teacher - false for admin
	Display::welcome();
	cin >> type;
	Display::clrscr();
	while ((current = UserAuthentication::login(cin,type)) < 0) { //Attempt Login, Repeats until login is successful, result is stored in 'current'
		cout << endl;
		Display::border();
		cerr << "Invalid Username and/or Password. Please try again." << endl << endl;
		Display::border();
	}
	gui(type); //Load successful login menu
}

void gui(bool type) {
	Display::clrscr();
	Display::border();
	cout << "You have successfully logged into the Library Management System." << endl;
	int choice = 0;
	Display::menu(type);
	Display::clrscr();
	cout << "Choice: ";
	cin >> choice;
	while (choice > 0) {
		Display::border();
		switch (choice) {
		case 1: //Search for Books
			Database::searchBooks(cin);
			break;
		case 2:
			if (type)  //Borrow Books
				Database::getReaders().at(current).borrowBooks(cin);
			else //Add Books for Admin
				cout << "To Be Implemented" << endl; 
			break;
		case 3: 
			if (type) //Return Books
				Database::getReaders().at(current).returnBooks(cin);
			else //Delete Books for Admin
				cout << "To Be Implemenented" << endl; 
			break;
		case 4: 
			if(type) //Reserve Books for Student/Teacher
				cout << "To Be Implemenented" << endl;
			else //Search Users for Admin
				cout << "To Be Implemenented" << endl;
			break;
		case 5: 
			if(type) //Cancel Reservations for Student/Teacher
				cout << "To be Implemeneted" << endl;
			else //Add Users for Admin
				cout << "To be Implemeneted" << endl;
			break;
		case 6: 
			if (type) //About Me for Student/Teacher
				Database::getReaders().at(current) << cout;
			else
				cout << "To Be Implemented" << endl; //Delete Users
			break;
		case 7:
			if(type) //About Me for Admin
				Database::getAdmins().at(current) << cout;
			else //Change Password for Student/Teacher
				Database::save();
			break;
		case 8:
			if (!type) { //Change Password for Admin
				cout << "To Be Implemented" << endl;
				break;
			}
		default: //Invalid Input
			cout << "Invalid selection. Please enter a valid ID." << endl;
		}
		Display::menu(type);
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