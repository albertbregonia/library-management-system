#pragma once
#include "Book.h"
#include <vector>

class Copy {
private:
	int id;
	Book* book;
	string borrower; //Current Borrower - SAVED AS USERNAME
	vector<string> reservers; //reservers, a vector is used instead of a queue to allow for easy deletion
	bool available;
	vector<long> reserveDates;
	long start; //borrow date
	long end; //expiration date
public:
	//Default Constructor
	Copy();
	Copy(int id, Book* book, string borrower, vector<string> reservers, bool available, vector<long> res, long start, long end);
	
	//Accessors
	int getID();
	Book* getBook();
	string getBorrower(); 
	vector<string>& getReservers();
	bool getAvailability();
	vector<long>& getReserveDates();
	long getStartDate();
	long getExpirationDate();

	//Mutators
	void setID(int id);
	void setBorrower(string borrower);
	void setReservers(vector<string> reservers);
	void setAvailability(bool available);
	void setReserveDates(vector<long> res);
	void setStartDate(long start);
	void setExpirationDate(long end);

	//Overloaded Operators
	ostream& operator<<(ostream& out);
	istream& operator>>(istream& in);
};