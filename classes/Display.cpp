#include <iostream>
#include <vector>
#include "Display.h"

using namespace std;

//Display Welcome Message on Database
void Display::welcome() {
	border();
	cout << "\tWelcome to the Library" << endl << endl;
	border();
	cout << "Are you a student/teacher?: \n\t1 - Yes\n\t0 - No" << endl << endl;
	cout << "Selection: ";
}

//Display Text Border
void Display::border() {cout << "=============================================" << endl << endl;}

//Displays options menu for users that are logged in
void Display::menu(bool type) {
	cout << endl;
	border();
	vector<string> options = { "Search for Books", "Add Books", "Delete Books", "Search for Users", "Add Users", "Delete Users", "About Me", "Change Password", "Log Out" };
	if (type) //Show Librarian Options
		options = { "Search for Books", "Borrow Books", "Return Books", "Reserve Books", "Cancel Reservations", "About Me", "Change Password", "Log Out" };
	for (int i = 0; i < options.size(); i++) {
		if (i == 0)
			cout << "What would you like to do?" << endl;
		if ((i < 8 && !type) || (i<7 && type))
			cout << "\t" << i + 1 << " -- " << options[i] << endl;
		else
			cout << "\t" << "0 -- " << options[i] << endl;
	}
}

void Display::clrscr() {
	for (int i = 0; i < 8; i++)
		cout << endl; //pseudo clear the screen
}