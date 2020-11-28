#pragma once
#include <vector>

#include "User.h"
#include "Book.h"

class Reader : public User
{
private:
	User login; //login info
	int term; //borrow period
	int max; //max # of copies a student is allowed to keep
	vector<Book> borrowed; //List of borrowed items
	vector<Book> reserved; //List of reserved items
	int penalties; //number of penalties
public:
	//Constructors
	Reader();
	Reader(string username, string password, int term, int max, vector<Book> borrowed, vector<Book> reserved);
	
	//Accessors
	User getLogin();
	int getTerm();
	int getMaxCopies();
	vector<Book>& getBorrowedBookList();
	vector<Book>& getReserved();
	int getPenalties();

	//Mutators
	void setLogin(User login);
	void setTerm(int term);
	void setMaxCopies(int max);
	void setBorrowed(vector<Book> borrowed);
	void setReserved(vector<Book> reserved);
	void setPenalties(int penalties);

	//Overloaded Operators
	ostream& operator<<(ostream& out);
	istream& operator>>(istream& in);
	bool operator==(Reader& r);

	//Readers may have penalties
	bool penalty();
};

