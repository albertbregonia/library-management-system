//Albert Bregonia 10/16

//Main System Launcher for the LMS

	/*To Do:
	* Date Counter - currently simple implementation
	* Borrow/Return Implementation
	* Register - I'm not sure if we're allowed to do this?
	*/

#include <iostream>

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

//Load into RAM the book/student data upon failure, the system aborts
void startup() {
	if (!Database::loadBooks())
		exit(-3);
	else if (!Database::loadStudents())
		exit(-4);
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
			Database::getStudents().at(current).borrow(cin);
			break;
		case 3: //Return Books - Submission 1
			break;
		case 4: //Reserve Books
			cout << "To be implemeneted" << endl;
			break;
		case 5: //Cancel Reservations
			cout << "To be implemeneted" << endl;
			break;
		case 6: //About Me
			Database::getStudents().at(current) << cout;
			break;
		case 7: //Change Password
			changePassword();
			Database::save();
			break;
		case 8:
			for (Book b : Database::getBooks())
				b << cout;
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
	if (pw == Database::getStudents().at(current).getPassword()) {
		cout << "Enter your new desired password: ";
		cin >> pw;
		for (Student s : Database::getStudents()) //change in the database as well as the current session
			if (s == Database::getStudents().at(current))
				Database::getStudents().at(current).setPassword(pw);
		cout << "Change successful." << endl;
	}
	else
		cout << "Change unsuccessful. Failed to verify user information." << endl;
}