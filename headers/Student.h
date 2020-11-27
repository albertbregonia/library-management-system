//Instantiation of Student Object

#pragma once
#include <string>
#include <vector>
#include "Book.h"
#include "Date.h"
using namespace std;

class Student {

private:
	string username;
	string password;
	int term; //borrow period
	int max; //max # of copies a student is allowed to keep
	vector<Book> borrowed; //List of borrowed items
	vector<Book> reserved; //List of reserved items
	int penalties; //number of penalties

public:
	//Constructors
	Student();
	Student(string username, string password, int term, int max, vector<Book> borrowed, vector<Book> reserved);

	//Accessors
	string getUsername();
	string getPassword();
	int getTerm();
	int getMaxCopies();
	vector<Book> getBorrowedBookList();
	vector<Book> getReserved();
	int getPenalties();

	//Mutators
	void setUsername(string username);
	void setPassword(string password);
	void setTerm(int term);
	void setMaxCopies(int max);
	void setBorrowed(vector<Book> borrowed);
	void setPenalties(int penalties);
	void setReserved(vector<Book> reserved);

	//Overloaded Operators
	ostream& operator<<(ostream& out) const;
	istream& operator>>(istream& in);
	bool operator==(Student& s) const;

	//User Actions
	void borrowBooks(istream& in);
	void returnBooks(istream& in);
	bool penalty();
};