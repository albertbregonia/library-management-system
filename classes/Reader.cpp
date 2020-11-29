#include "Reader.h"
#include <iostream>
#include "Database.h"
#include "Display.h"

Reader::Reader(): //Reader default is the same as student default
	User(),
	term(30), //by default max borrow period is <=30
	max(5), //by default max 5 books can be borrowed
	borrowed(vector<Copy>()),
	penalties(0),
	reserved(vector<Copy>())
{}

Reader::Reader(string username, string password, int term, int max, vector<Copy> borrowed, vector<Copy> reserved):
	User(username, password),
	term(term),
	max(max),
	borrowed(borrowed),
	penalties(0),
	reserved(reserved)
{}

//Accessor
int Reader::getTerm() { return term; }
int Reader::getMaxCopies() { return max; }
vector<Copy>& Reader::getBorrowedBookList() { return borrowed; }
vector<Copy>& Reader::getReserved() { return reserved; }
int Reader::getPenalties() { return penalties; }

//Mutators
void Reader::setTerm(int term) { this->term = term; }
void Reader::setMaxCopies(int max) { this->max = max; }
void Reader::setBorrowed(vector<Copy> borrowed) { this->borrowed = borrowed; }
void Reader::setPenalties(int penalties) { this->penalties = penalties; }
void Reader::setReserved(vector<Copy> reserved) { this->reserved = reserved; }

//Reads in a single reader from an istream and adds it to the database
istream& Reader::operator>>(istream& in) {
	string line;
	if (!in.eof())
		for (int i = 0; i < 6; i++) {
			getline(in, line);
			if (line.empty())
				break;
			switch (i) {
			case 0:
				setUsername(line);
				break;
			case 1:
				setPassword(line);
				break;
			case 2:
				term = stoi(line);
				break;
			case 3:
				max = stoi(line);
				break;
			case 4:
				borrowed.clear();
				for (string id : Database::split(line))
					if (stoi(id) > 0)
						borrowed.push_back(Database::getCopies().at(Database::getCopyByID(stoi(id))));
				break;
			case 5:
				break;
				//line delimiter
			}
		}
	return in;
}

//Write to ostream
ostream& Reader::operator<<(ostream& out) {
	if (&out == &cout) { //Console Display
		out << "Username: " << getUsername() << endl;
		out << "Password: " << getPassword() << endl;
		out << "Borrow Period: " << term << endl;
		out << "Max Number of Books you are able to Borrow: " << max << endl;
		out << "Currently Borrowed Books: " << endl << endl;
		for (Copy c : borrowed) {
			c << out;
			out << endl;
		}
	}
	else { //Write to File
		out << endl << getUsername() << endl;
		out << getPassword() << endl;
		out << term << endl;
		out << max << endl;
		if (!borrowed.empty())
			for (Copy c : borrowed) //puts all books IDs on a line delimited by a space
				out << c.getID() << " ";
		else
			out << -1 << " "; //Indicates no books borrowed
		out << endl << "----------------";
	}
	return out;
}

bool Reader::operator==(Reader& r) { return getUsername() == r.getUsername() && getPassword() == r.getPassword(); }

//Converts strings to lowercase
static string toLower(string s) {
	string temp = "";
	for (char c : s)
		temp += tolower(c);
	return temp;
}

//Checks and issues a penalty when they have overdue books
bool Reader::penalty() {
	for (Copy c : borrowed)
		if (Date::getDays() > c.getExpirationDate()) {
			cout << "You have overdue book(s). You will not be allowed to borrow any more books." << endl;
			penalties++; //Increase # of penalties
			/*
			* if(penalty==5)
			*	max--;
			*/
			return true;
		}
	return false;
}

//Option 1 - WIP
void Reader::searchBooks(istream& in) {
	//Display
	int choice;
	cout << "Search By: " << endl;
	string keys[] = { "ISBN", "Title", "Author", "Category" };
	for (int i = 0; i < 4; i++)
		cout << "\t " << i << " - " << keys[i] << endl;
	cout << endl << "Selection: ";
	in >> choice;
	cout << endl;
	Display::border();
	//Search
	string isbn, title, author, category;
	switch (choice) {
	case 0: //ISBN Search
		cout << "Enter an ISBN to search for: ";
		cin >> isbn;
		cout << endl;
		Display::border();
		for (Book b : Database::getBooks())
			if (b.getISBN() == isbn) { //Find book with ISBN
				b << cout; //Print Book Info
				cout << "***IDs: ";
				for (Copy c : Database::getCopies()) //Find all IDs of that Book
					if (c.getBook()->getISBN() == isbn)
						cout << c.getID() << " ";
				cout << endl << endl;
				return; //There is only 1 ISBN per book
			}
		break;
	case 1: //Title Search
		cout << "Enter a title to search for: ";
		cin >> title;
		title = toLower(title); //Converted to lowercase to ignore capitals
		cout << endl;
		Display::border();
		for (Book b : Database::getBooks())
			if (toLower(b.getTitle()).find(title) != string::npos) { //Find book with title or string in title
				b << cout; //Print Book Info
				string t = b.getTitle();
				cout << "***IDs: ";
				for (Copy c : Database::getCopies()) //Find all IDs of that Book
					if (c.getBook()->getTitle() == t)
						cout << c.getID() << " ";
				cout << endl << endl;
			}
		break;
	case 2: //Author Based Search
		break;
	case 3: //Category Based Search
		break;
	default: //Invalid Inputs
		cout << "Invalid Input." << endl;
		Display::border();
		break;
	}
}

//Option 2 - Boorow Books
void Reader::borrowBooks(istream& in) {
	if (penalty()) //Check for penalty
		return;
	if (getMaxCopies() > getBorrowedBookList().size()) { //Check if they haven't checked out more than their maximum
		int id;
		cout << "ID of desired book: "; //Input for desired book ID
		in >> id;
		if (Database::getCopyByID(id) < 0) { //Check for invalid ID
			cout << "Invalid ID. A book with that ID was not found." << endl;
			return;
		}
		Copy* desired = &Database::getCopies().at(Database::getCopyByID(id)); //A pointer is used here to modify the value directly in the database instead of a copy of the value
		if (desired->getBorrower() == "none") { //If nobody has borrowed the book, set the book's information to that of the borrower
			desired->setBorrower(getUsername());
			desired->setStartDate(Date::getDays()); //set start period to current date
			desired->setExpirationDate(Date::getDays() + 30); //30 days from current date is the expiration
			getBorrowedBookList().push_back(*desired); //add to borrowed book list
			Database::save(); //write back to database files
			cout << endl << "Successfully borrowed Book #" << id << endl << endl << endl;
			Database::getCopies().at(Database::getCopyByID(id)) << cout; //Print recently borrowed book info
			return;
		}
		else
			cout << "Unfortunately, this book has already been borrowed. Please choose a different book." << endl;
	}
	else if (getMaxCopies() == 0)
		cout << "You have been issued a penalty! You are not allowed to borrow another book." << endl;
	else
		cout << "You have reached your limit on books! Please return a book. " << endl;
}

//Option 3 - Return Books
void Reader::returnBooks(istream& in) {
	penalty(); //Check for penalty and issue penalty if a book is overdue
	int id;
	cout << "ID of book to return: "; //Input for desired book ID
	in >> id;
	if (Database::getCopyByID(id) < 0) { //Check for invalid ID
		cout << "Invalid ID. A book with that ID was not found." << endl;
		return;
	}
	else {
		Copy* desired = &Database::getCopies().at(Database::getCopyByID(id)); //A pointer is used here to modify the value directly in the database instead of a copy of the value
		for (int i = 0; i < getBorrowedBookList().size(); i++)
			if (getBorrowedBookList().at(i).getID() == id) { //Check if the user has borrowed a book with the given ID
				//Reset Book attributes
				desired->setBorrower("none");
				desired->setStartDate(0);
				desired->setExpirationDate(0);
				getBorrowedBookList().erase(getBorrowedBookList().begin() + i); //remove from borrowed list
				Database::save(); //write back to database files
				cout << endl << "Successfully returned Book #" << id << endl << endl << endl;
				Database::getCopies().at(Database::getCopyByID(id)) << cout; //Print recently returned book info
				return;
			}
		cout << "Error. You have not borrowed a book with the ID #" << id << endl;
	}
}