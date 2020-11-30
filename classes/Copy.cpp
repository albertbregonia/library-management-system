#include "Copy.h"
#include <iostream>
#include "Database.h"

//Constructors
Copy::Copy() :
	id(-2),
	book(NULL),
	borrower("none"),
	reservers(vector<string>()),
	available(true),
	reserveDates(vector<long>()),
	start(0),
	end(0)
{}

Copy::Copy(int id, Book* book, string borrower, vector<string> reservers, bool available, vector<long> res, long start, long end) :
	id(id),
	book(book),
	borrower(borrower),
	reservers(reservers),
	available(available),
	reserveDates(res),
	start(start),
	end(end)
{}

//Accessors
int Copy::getID() { return id; }
Book* Copy::getBook() { return book; }
string Copy::getBorrower() { return borrower; }
vector<string>& Copy::getReservers() { return reservers; }
bool Copy::getAvailability() { return available; }
vector<long>& Copy::getReserveDates() { return reserveDates; }
long Copy::getStartDate() { return start; }
long Copy::getExpirationDate() { return end; }

//Mutators
void Copy::setID(int id) { this->id = id; }
void Copy::setBorrower(string borrower) { this->borrower = borrower; }
void Copy::setAvailability(bool available) { this->available = available; }
void Copy::setReservers(vector<string> reservers) { this->reservers = reservers; }
void Copy::setReserveDates(vector<long> res) { this->reserveDates = res; }
void Copy::setStartDate(long start) { this->start = start; }
void Copy::setExpirationDate(long end) { this->end = end; }

//Overloaded Operators
ostream& Copy::operator<<(ostream& out){
	string res;
	if (reservers.empty())
		res = "none";
	else
		for (string u : reservers)
			res += u + " ";
	string resDates;
	if (reserveDates.empty())
		resDates = "-1";
	else
		for (long l : reserveDates)
			resDates += to_string(l) + " ";
	if (&out == &cout) { //Console Display
		out << "ID: " << id << endl;
		out << "Book (ISBN): " << book->getISBN() << endl;
		out << "Borrower: " << borrower << endl;
		out << "Reservers: " << res << endl;
		out << "Available: " << available << endl;
		out << "Reserve Date: " << resDates << endl;
		out << "Borrow Date: " << start << endl;
		out << "Expiration Date: " << end << endl;
	}
	else { //Write to File
		out << endl << id << endl;
		out << book->getISBN() << endl;
		out << borrower << endl;
		out << res << endl;
		out << available << endl;
		out << resDates << endl;
		out << start << endl;
		out << end << endl;
		out << "----------------";
	}
	return out;
}

//Reads in a single book from a stream and adds it to the book database
istream& Copy::operator>>(istream& in) {
	string line;
	if (!in.eof())
		for (int i = 0; i < 9; i++) {
			getline(in >> ws, line);
			if (line.empty())
				break;
			switch (i) {
			case 0:
				id = stoi(line);
				break;
			case 1:
				book = &Database::getBooks().at(Database::getBookByISBN(line));
				break;
			case 2:
				borrower = line;
				break;
			case 3:
				reservers.clear();
				for (string username : Database::split(line))
					if (username != "none")
						reservers.push_back(username);
				break;
			case 4:
				available = stoi(line);
				break;
			case 5:
				reserveDates.clear();
				for (string date : Database::split(line))
					if (stol(date)>=0)
						reserveDates.push_back(stol(date));
				break;
			case 6:
				start = stol(line);
				break;
			case 7:
				end = stol(line);
				break;
			case 8: //line delimiter
				break;
			}
		}
	return in;
}