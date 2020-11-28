#include "Reader.h"
#include "Database.h"
#include <iostream>

Reader::Reader(): //Reader default is the same as student default
	login(User()),
	term(30), //by default max borrow period is <=30
	max(5), //by default max 5 books can be borrowed
	borrowed(vector<Book>()),
	penalties(0),
	reserved(vector<Book>())
{}

Reader::Reader(string username, string password, int term, int max, vector<Book> borrowed, vector<Book> reserved):
	login(User(username,password)),
	term(term),
	max(max),
	borrowed(borrowed),
	penalties(0),
	reserved(reserved)
{}

//Accessor
User Reader::getLogin() { return login; }
int Reader::getTerm() { return term; }
int Reader::getMaxCopies() { return max; }
vector<Book>& Reader::getBorrowedBookList() { return borrowed; }
vector<Book>& Reader::getReserved() { return reserved; }
int Reader::getPenalties() { return penalties; }

//Mutators
void Reader::setLogin(User login) { this->login = login; }
void Reader::setTerm(int term) { this->term = term; }
void Reader::setMaxCopies(int max) { this->max = max; }
void Reader::setBorrowed(vector<Book> borrowed) { this->borrowed = borrowed; }
void Reader::setPenalties(int penalties) { this->penalties = penalties; }
void Reader::setReserved(vector<Book> reserved) { this->reserved = reserved; }

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
				login.setUsername(line);
				break;
			case 1:
				login.setPassword(line);
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
						borrowed.push_back(Database::getBooks().at(Database::getBookByID(stoi(id))));
				break;
			case 5: 
				//line delimiter
			}
		}
	return in;
}

//Write to ostream
ostream& Reader::operator<<(ostream& out) {
	if (&out == &cout) { //Console Display
		out << "Username: " << login.getUsername() << endl;
		out << "Password: " << login.getPassword() << endl;
		out << "Borrow Period: " << term << endl;
		out << "Max Number of Books you are able to Borrow: " << max << endl;
		out << "Currently Borrowed Books: " << endl << endl;
		for (Book b : borrowed) {
			b << out;
			out << endl;
		}
	}
	else { //Write to File
		out << login.getUsername() << endl;
		out << login.getPassword() << endl;
		out << term << endl;
		out << max << endl;
		if (!borrowed.empty())
			for (Book b : borrowed) //puts all books IDs on a line delimited by a space
				out << b.getID() << " ";
		else
			out << -1 << " "; //Indicates no books borrowed
		out << endl << "----------------" << endl;
	}
	return out;
}

bool Reader::operator==(Reader& r) { return login.getUsername() == r.getUsername() && login.getPassword() == r.getPassword(); }

//Checks and issues a penalty when they have overdue books
bool Reader::penalty() {
	for (Book b : borrowed)
		if (Date::getDays() > b.getExpirationDate()) {
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