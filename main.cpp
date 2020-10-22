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
#include "Startup.h"

using namespace std;

void startup();
void start();
void gui(bool teacher);

//Load into RAM the book/student data
void startup() {
	if (!Startup::loadBooks() || !Startup::loadStudents())
		exit(-1);
}

//Welcome and Login Menu
void start() {
	Display::welcome();
	int choice;
	cin >> choice;
	if (choice == 0)
		UserAuthentication::signup(cin);
	else {
		while (!UserAuthentication::login(cin)) { //Attempt Login, Repeats until login is successful
			cout << endl;
			Display::border();
			cerr << "Invalid Username and/or Password. Please try again." << endl << endl;
			Display::border();
		}
		gui(false); //Load successful login menu based on 'false' for student or 'true' for teacher
	}
	cout << "You have successfully logged out of the Library Management System. Have a great day." << endl;
}

void gui(bool teacher) {
	Display::clrscr();
	cout << endl;
	Display::border();
	cout << "You have successfully logged into the Library Management System." << endl;
	int choice = 0;
	Display::menu(teacher);
	cin >> choice;
	while (choice > 0) {
		switch (choice) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		default:
			cout << "Invalid selection. Please enter a valid ID." << endl;
		}
		Display::menu(teacher);
		cin >> choice;
		cout << endl << endl;
		Display::border();
		Display::clrscr();
	}
	cout << "You have successfully logged out of the Library Management System. Have a great day." << endl;
	Display::clrscr();
	start();
}

int main() {
	startup();
	start();
	return 0;
}