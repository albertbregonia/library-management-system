#include "Reader.h"
#include <iostream>
#include "Database.h"

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
		out << getUsername() << endl;
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