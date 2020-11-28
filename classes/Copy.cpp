#include "Copy.h"

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