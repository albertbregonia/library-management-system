//Albert Bregonia 10/16

#include <iostream>
#include "Display.h"

using namespace std;

//Display Welcome Message on Startup
void Display::welcome() {
	border();
	cout << "Welcome to the Library" << endl << endl;
	border();
	cout << "What would you like to do?" << endl;
	cout << "\t0 -- Sign Up" << endl;
	cout << "\tDefault -- Login" << endl << endl;
}

//Display Text Border
void Display::border() {cout << "=============================================" << endl << endl;}

//Displays options menu for users that are logged in
void Display::menu(bool teacher) {
	cout << endl;
	border();
	//As of 10/16, type is supposed to be 's' for student and 't' for teacher to change options
	string options[] = { "Search for Books", "Borrow Books", "Return Books", "Reserve Books", "Cancel Reservations", "About Me", "Change Password", "Log Out" };
	for (int i = 0; i < sizeof(options) / sizeof(string); i++) {
		if (i == 0)
			cout << "What would you like to do?" << endl;
		if (i < 7)
			cout << "\t" << i + 1 << " -- " << options[i] << endl;
		else
			cout << "\t" << "0 -- " << options[i] << endl;
	}
}

void Display::clrscr() {
	for (int i = 0; i < 50; i++)
		cout << endl; //clear the screen
}