//Albert Bregonia 10/16

//Main System Launcher for the LMS

	/*To Do:
	* File Database
	* User Authentication
	* Date Counter
	* Borrow/Return Implementation
	* Register
	*/

#include <iostream>
#include <vector>
#include <fstream>

#include "Display.h"
#include "UserAuth.h"
#include "Startup.h"

using namespace std;

void startup();
void start();
void gui(char type);

int main() {
	startup();
	start();
	return 0;
}

void start() {
	Display::welcome(); //Welcome Screen
	int choice;
	cin >> choice;
	if (choice == 0)
		UserAuthentication::signup(cin);
	else {
		while (!UserAuthentication::login(cin)) {} //Attempt Login, Repeats until login is successful
		gui('s');
	}
	cout << "You have successfully logged out of the Library Management System. Have a great day." << endl;
}

void startup() {
	if (!Startup::loadBooks() || !Startup::loadStudents())
		exit(-1);
}



void gui(char type) {
	cout << endl;
	Display::border();
	cout << "You have successfully logged into the Library Management System." << endl;
	int choice = 0;
	Display::menu(type);
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
		Display::menu(type);
		cin >> choice;
		cout << endl << endl;
		Display::border();
	}
	cout << "You have successfully logged out of the Library Management System. Have a great day." << endl;
	for (int i = 0; i < 50; i++)
		cout << endl; //clear the screen
	start();
}
