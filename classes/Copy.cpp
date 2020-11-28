#include "Copy.h"
#include <iostream>
#include "Database.h"

//Constructors
Copy::Copy() :
	id(-2),
	book(Book()),
	borrower("none"),
	reserver("none"),
	available(true),
	reserveDate(0),
	start(0),
	end(0)
{}

Copy::Copy(int id, Book book, string borrower, string reserver, bool available, long res, long start, long end) :
	id(id),
	book(book),
	borrower(borrower),
	reserver(reserver),
	available(available),
	reserveDate(res),
	start(start),
	end(end)
{}

//Accessors
int Copy::getID() { return id; }
Book Copy::getBook() { return book; }
string Copy::getBorrower() { return borrower; }
string Copy::getReserver() { return reserver; }
bool Copy::getAvailability() { return available; }
long Copy::getReserveDate() { return reserveDate; }
long Copy::getStartDate() { return start; }
long Copy::getExpirationDate() { return end; }

//Mutators
void Copy::setID(int id) { this->id = id; }
void Copy::setBorrower(string borrower) { this->borrower = borrower; }
void Copy::setAvailability(bool available) { this->available = available; }
void Copy::setReserver(string reserver) { this->reserver = reserver; }
void Copy::setReserveDate(long res) { this->reserveDate = res; }
void Copy::setStartDate(long start) { this->start = start; }
void Copy::setExpirationDate(long end) { this->end = end; }

//Overloaded Operators
ostream& Copy::operator<<(ostream& out){
	if (&out == &cout) { //Console Display
		out << "ID: " << id << endl;
		out << "Book (ISBN): " << book.getISBN() << endl;
		out << "Borrower: " << borrower << endl;
		out << "Reserver: " << reserver << endl;
		out << "Available: " << available << endl;
		out << "Reserve Date: " << reserveDate << endl;
		out << "Borrow Date: " << start << endl;
		out << "Expiration Date: " << end << endl;
	}
	else { //Write to File
		out << id << endl;
		out << book.getISBN() << endl;
		out << borrower << endl;
		out << reserver << endl;
		out << available << endl;
		out << reserveDate << endl;
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
			getline(in, line);
			if (line.empty())
				break;
			switch (i) {
			case 0:
				id = stoi(line);
				break;
			case 1:
				book = Database::getBooks().at(Database::getBookByISBN(line));
				break;
			case 2:
				borrower = line;
				break;
			case 3:
				reserver = line;
				break;
			case 4:
				available = stoi(line);
				break;
			case 5:
				reserveDate = stol(line);
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