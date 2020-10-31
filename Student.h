//Instantiation of Student Object

#pragma once
#include <string>
#include <vector>
#include "Book.h"
using namespace std;

class Student {

private:
	string username;
	string password;
	int term; //borrow period
	int max; //max # of copies a student is allowed to keep
	vector<Book> borrowed; //List of borrowed items

public:
	//Constructors
	Student();
	Student(string username, string password, int term, int max, vector<Book> borrowed);

	//Accessors
	string getUsername();
	string getPassword();
	int getTerm();
	int getMaxCopies();
	vector<Book> getBorrowedBookList();

	//Mutators
	void setUsername(string username);
	void setPassword(string password);
	void setTerm(int term);
	void setMaxCopies(int max);
	void setBorrowedBooks(vector<Book> borrowed);

	//Overloaded Operators
	ostream& operator<<(ostream& out) const;
	istream& operator>>(istream& in);
};