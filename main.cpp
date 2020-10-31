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

Student current; //Current Student Info, if successful

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
	cin >> choice;
	if (choice == 0)
		UserAuthentication::signup(cin);
	else {
		while (!UserAuthentication::login(cin,current)) { //Attempt Login, Repeats until login is successful, result is stored in 'current'
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
	cin >> choice;
	while (choice > 0) {
		Display::border();
		switch (choice) {
		case 1: //Search for Books
			break;
		case 2: //Borrow Books - Submission 1
			break;
		case 3: //Return Books - Submission 1
			break;
		case 4: //Reserve Books
			break;
		case 5: //Cancel Reservations
			break;
		case 6: //About Me
			current << cout;
			break;
		case 7: //Change Password
			changePassword();
			Database::save();
			break;
		default: //Invalid Input
			cout << "Invalid selection. Please enter a valid ID." << endl;
		}
		Display::menu();
		Display::clrscr();
		cin >> choice;
		cout << endl << endl;
	}
	Display::clrscr();
	Display::clrscr();
	Display::border();
	cout << "You have successfully logged out of the Library Management System. Have a great day." << endl << endl;
	start();
}

//Option 7 - Change Current User's Password
void changePassword() {
	string pw;
	cout << "Enter your current password: ";
	cin >> pw;
	if (pw == current.getPassword()) {
		cout << "Enter your new desired password: ";
		cin >> pw;
		current.setPassword(pw);
		cout << "Change successful." << endl;
	}
	else
		cout << "Change unsuccessful. Failed to verify user information." << endl;
}