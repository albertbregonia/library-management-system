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
void Copy::setBook(Book* book) { this->book = book; }
void Copy::setBorrower(string borrower) { this->borrower = borrower; }
void Copy::setAvailability(bool available) { this->available = available; }
void Copy::setReservers(vector<string> reservers) { this->reservers = reservers; }
void Copy::setReserveDates(vector<long> res) { this->reserveDates = res; }
void Copy::setStartDate(long start) { this->start = start; }
void Copy::setExpirationDate(long end) { this->end = end; }

//Overloaded Operators
ostream& operator<<(ostream& out, Copy& c){
	string res;
	if (c.reservers.empty())
		res = "none";
	else
		for (string u : c.reservers)
			res += u + " ";
	string resDates;
	if (c.reserveDates.empty())
		resDates = "-1";
	else
		for (long l : c.reserveDates)
			resDates += to_string(l) + " ";
	if (&out == &cout) { //Console Display
		out << "ID: " << c.id << endl;
		out << "Book (ISBN): " << c.book->getISBN() << endl;
		out << "Borrower: " << c.borrower << endl;
		out << "Reservers: " << res << endl;
		out << "Available: " << c.available << endl;
		out << "Reserve Date: " << resDates << endl;
		out << "Borrow Date: " << c.start << endl;
		out << "Expiration Date: " << c.end << endl;
	}
	else { //Write to File
		out << endl << c.id << endl;
		out << c.book->getISBN() << endl;
		out << c.borrower << endl;
		out << res << endl;
		out << c.available << endl;
		out << resDates << endl;
		out << c.start << endl;
		out << c.end << endl;
		out << "----------------";
	}
	return out;
}

//Reads in a single book from a stream and adds it to the book database
istream& operator>>(istream& in, Copy& c) {
	string line;
	if (!in.eof())
		for (int i = 0; i < 9; i++) {
			getline(in >> ws, line);
			if (line.empty())
				break;
			switch (i) {
			case 0:
				c.id = stoi(line);
				break;
			case 1:
				c.book = &Database::getBooks().at(Database::getBookByISBN(line));
				break;
			case 2:
				c.borrower = line;
				break;
			case 3:
				c.reservers.clear();
				for (string username : Database::split(line))
					if (username != "none")
						c.reservers.push_back(username);
				break;
			case 4:
				c.available = stoi(line);
				break;
			case 5:
				c.reserveDates.clear();
				for (string date : Database::split(line))
					if (stol(date)>=0)
						c.reserveDates.push_back(stol(date));
				break;
			case 6:
				c.start = stol(line);
				break;
			case 7:
				c.end = stol(line);
				break;
			case 8: //line delimiter
				break;
			}
		}
	return in;
}
