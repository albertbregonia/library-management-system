#include <iostream>
#include "Student.h"
#include "Database.h"

//Constructors
Student::Student(): 
	info(Reader()) {}

Student::Student(string username, string password, int term, int max, vector<Book> borrowed, vector<Book> reserved):
	info(Reader(username, password, term, max, borrowed, reserved)) {}

//Accessor
Reader Student::getInfo() { return info; }

//Mutator
Reader Student::setInfo(Reader r) { this->info = r; }

//Option 2 - Boorow Books
void Student::borrowBooks(istream& in) {
	if (penalty()) //Check for penalty
		return;
	if (info.getMaxCopies() > info.getBorrowedBookList().size()) { //Check if they haven't checked out more than their maximum
		int id;
		cout << "ID of desired book: "; //Input for desired book ID
		in >> id;
		if (Database::getBookByID(id) < 0) { //Check for invalid ID
			cout << "Invalid ID. A book with that ID was not found." << endl;
			return;
		}
		Book* desired = &Database::getBooks().at(Database::getBookByID(id)); //A pointer is used here to modify the value directly in the database instead of a copy of the value
		if (desired->getBorrower() == "none") { //If nobody has borrowed the book, set the book's information to that of the borrower
			desired->setBorrower(info.getLogin().getUsername());
			desired->setStartDate(Date::getDays()); //set start period to current date
			desired->setExpirationDate(Date::getDays() + 30); //30 days from current date is the expiration
			info.getBorrowedBookList().push_back(*desired); //add to borrowed book list
			Database::save(); //write back to database files
			cout << endl << "Successfully borrowed Book #" << id << endl << endl << endl;
			Database::getBooks().at(Database::getBookByID(id)) << cout; //Print recently borrowed book info
			return;
		}
		else
			cout << "Unfortunately, this book has already been borrowed. Please choose a different book." << endl;
	}
	else if(info.getMaxCopies() == 0)
		cout << "You have been issued a penalty! You are not allowed to borrow another book." << endl;
	else
		cout << "You have reached your limit on books! Please return a book. " << endl;
}

//Option 3 - Return Books
void Student::returnBooks(istream& in) {
	penalty(); //Check for penalty and issue penalty if a book is overdue
	int id;
	cout << "ID of book to return: "; //Input for desired book ID
	in >> id;
	if (Database::getBookByID(id) < 0) { //Check for invalid ID
		cout << "Invalid ID. A book with that ID was not found." << endl;
		return;
	}
	else {
		Book* desired = &Database::getBooks().at(Database::getBookByID(id)); //A pointer is used here to modify the value directly in the database instead of a copy of the value
		for (int i=0; i<info.getBorrowedBookList().size(); i++)
			if (info.getBorrowedBookList().at(i).getID() == id) { //Check if the user has borrowed a book with the given ID
				//Reset Book attributes
				desired->setBorrower("none");
				desired->setStartDate(0);
				desired->setExpirationDate(0);
				info.getBorrowedBookList().erase(info.getBorrowedBookList().begin() + i); //remove from borrowed list
				Database::save(); //write back to database files
				cout << endl << "Successfully returned Book #" << id << endl << endl << endl;
				Database::getBooks().at(Database::getBookByID(id)) << cout; //Print recently returned book info
				return;
			}
		cout << "Error. You have not borrowed a book with the ID #" << id << endl;
	}
}

	