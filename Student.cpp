#include <iostream>
#include "Student.h"
#include "Database.h"

//Constructors
Student::Student(): 
	username("none"),
	password("none"),
	term(30),
	max(5),
	borrowed(vector<Book>())
{}
Student::Student(string username, string password, int term, int max, vector<Book> borrowed):
	username(username),
	password(password),
	term(term),
	max(max),
	borrowed(borrowed)
{}
//Accessors
string Student::getUsername() { return username; }
string Student::getPassword() { return password; }
int Student::getTerm() { return term; }
int Student::getMaxCopies() { return max; }
vector<Book> Student::getBorrowedBookList() { return borrowed; }

//Mutators
void Student::setUsername(string username) { this->username = username; }
void Student::setPassword(string password) { this->password = password; }
void Student::setTerm(int term) { this->term = term; }
void Student::setMaxCopies(int max) { this->max = max; }
void Student::setBorrowedBooks(vector<Book> borrowed) { this->borrowed = borrowed; }

//Overloaded Operators
ostream& Student::operator<<(ostream& out) const {
	if (&out == &cout) { //Console Display
		out << "Username: " << username << endl;
		out << "Password: " << password << endl;
		out << "Borrow Period: " << term << endl;
		out << "Max Number of Books you are able to Borrow: " << max << endl;
		out << "Currently Borrowed Books: " << endl << endl;
		for (Book b : borrowed) {
			b << out;
			out << endl;
		}
	}
	else { //Write to File
		out << username << endl;
		out << password << endl;
		out << term << endl;
		out << max << endl;
		if (!borrowed.empty())
			for (Book b : borrowed)
				out << b.getID() << " ";
		else
			out << -10 << " "; //Indicates no books borrowed
		out << endl << "----------------" << endl;
	}
	return out;
}

istream& Student::operator>>(istream& in) {
	string line;
	if (!in.eof())
		for (int i = 0; i < 6; i++) {
			getline(in,line);
			if (line.empty())
				break;
			switch (i) {
				case 0:
					username = line;
					break;
				case 1:
					password = line;
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
						if(stoi(id)>0)
							borrowed.push_back(Database::getBooks().at(Database::getBookByID(stoi(id))));
					break;
				case 5: //line delimiter
					Database::getStudents().push_back(*this);
			}
		}
	return in;
}

bool Student::operator==(Student& s) const { return username == s.getUsername() && password == s.getPassword(); }

//Option 2 - Boorow Books
void Student::borrowBooks(istream& in) {
	if (max > borrowed.size()) { //Check if they haven't checked out more than their maximum
		int id;
		cout << "ID of desired book: "; //Input for desired book ID
		in >> id;
		if (Database::getBookByID(id) < 0) { //Check for invalid ID
			cout << "Invalid ID. A book with that ID was not found." << endl;
			return;
		}
		Book* desired = &Database::getBooks().at(Database::getBookByID(id));
		if (desired->getBorrower() == "none") { //If nobody has borrowed the book, set the book's information to that of the borrower
			desired->setBorrower(username);
			desired->setStartDate(Date::getDays()); //set start period to current date
			desired->setExpirationDate(Date::getDays() + 6); //currently at 30 seconds or 6 days of expiration
			borrowed.push_back(*desired);
			Database::save(); //write back to database files
			cout << endl << "Successfully borrowed Book #" << id << endl << endl << endl;
			Database::getBooks().at(Database::getBookByID(id)) << cout; //Print recently borrowed book info
			return;
		}
		else
			cout << "Unfortunately, this book has already been borrowed. Please choose a different book." << endl;
	}
	else
		cout << "You have reached your limit on books! Please return a book. " << endl;
}

void Student::returnBooks(istream& in) {
	int id;
	cout << "ID of book to return: "; //Input for desired book ID
	in >> id;
	if (Database::getBookByID(id) < 0) { //Check for invalid ID
		cout << "Invalid ID. A book with that ID was not found." << endl;
		return;
	}
	else {
		Book* desired = &Database::getBooks().at(Database::getBookByID(id));
		for (int i=0; i<borrowed.size(); i++)
			if (borrowed.at(i).getID() == id) { //Check if the user has borrowed a book with the given ID
				desired->setBorrower("none"); //Reset Book attributes
				desired->setStartDate(0);
				desired->setExpirationDate(0);
				borrowed.erase(borrowed.begin() + i); //remove from borrowed list
				Database::save(); //write back to database files
				cout << endl << "Successfully returned Book #" << id << endl << endl << endl;
				Database::getBooks().at(Database::getBookByID(id)) << cout; //Print recently returned book info
				return;
			}
		cout << "Error. You have not borrowed a book with the ID #" << id << endl;
	}
}

/*checks and issues penalties when they have overdue books*/
void penalty(){

}
	