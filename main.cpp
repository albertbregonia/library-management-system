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
		cout << b << endl;
	cout << "\n\n\n\n";
	for (Copy c : Database::getCopies())
		cout << c << endl;
	cout << "\n\n\n\n";
}

void printAccounts() { //Test overloaded operators for accounts
	for (Reader r : Database::getReaders())
		cout << r << endl;
	for (Librarian l : Database::getAdmins())
		cout << l << endl;
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
	//printBooks();
	//printAccounts();
}

//Welcome and Login Menu
void start() {
	Display::welcome();
	int choice = Database::inputHandler(cin); //take in input
	bool type = choice != 0; // true for student/teacher - false for admin
	string info = (type) ? "Student/Teacher" : "Administrator";
	Display::clrscr();
	cout << "You are a [" << info << "]" << endl;
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
				Database::getAdmins().at(current).addBook(cin);
			break;
		case 3: 
			if (type) //Return Books
				Database::getReaders().at(current).returnBooks(cin);
			else //Delete Books for Admin
				Database::getAdmins().at(current).deleteBook(cin);
			break;
		case 4: 
			if (type) //Reserve Books for Student/Teacher
				Database::getReaders().at(current).reserveBooks(cin);
			else //Search Users for Admin
				Database::getAdmins().at(current).searchUsers(cin);
			break;
		case 5: 
			if (type) //Cancel Reservations for Student/Teacher
				Database::getReaders().at(current).cancelReserve(cin);
			else //Add Users for Admin
				Database::getAdmins().at(current).addUser(cin);
			break;
		case 6: 
			if (type) //Renew Books for Student/Teacher
				Database::getReaders().at(current).renewBooks(cin);
			else
				Database::getAdmins().at(current).deleteUser(cin);
			break;
		case 7:
			if(type) //About Me for Admin
				cout << Database::getReaders().at(current);
			else
				cout << Database::getAdmins().at(current);
			break;
		case 8:
			if (type) //Change Password for Student/Teacher
				Database::changePassword(cin, Database::getReaders().at(current));
			else //Change Password for Admin
				Database::changePassword(cin, Database::getAdmins().at(current));
			Database::save();
			break;
		case 9: //Recommend Books
			if (type)
				Database::getReaders().at(current).recommendBooks();
			break;
		default: //Invalid Input
			cout << "Invalid selection. Please enter a valid ID." << endl;
		}
		Display::menu(type);
		Display::clrscr();
		cout << "Time is currently: " << Date::getDays() << endl;
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