#pragma once
#include "Book.h"

class Copy {
private:
	int id;
	Book* book;
	string borrower; //Current Borrower - SAVED AS USERNAME
	string reserver; //Current Reserver - SAVED AS USERNAME
	bool available;
	long reserveDate;
	long start; //borrow date
	long end; //expiration date
public:
	//Default Constructor
	Copy();
	Copy(int id, Book* book, string borrower, string reserver, bool available, long res, long start, long end);
	
	//Accessors
	int getID();
	Book* getBook();
	string getBorrower(); 
	string getReserver();
	bool getAvailability();
	long getReserveDate();
	long getStartDate();
	long getExpirationDate();

	//Mutators
	void setID(int id);
	void setBorrower(string borrower);
	void setReserver(string reserver);
	void setAvailability(bool available);
	void setReserveDate(long res);
	void setStartDate(long start);
	void setExpirationDate(long end);

	//Overloaded Operators
	ostream& operator<<(ostream& out);
	istream& operator>>(istream& in);
};