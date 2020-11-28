#pragma once
#include <vector>
#include "User.h"
#include "Copy.h"

class Reader : public User
{
private:
	int term; //borrow period
	int max; //max # of copies a student is allowed to keep
	vector<Copy> borrowed; //List of borrowed items
	vector<Copy> reserved; //List of reserved items
	int penalties; //number of penalties
public:
	//Constructors
	Reader();
	Reader(string username, string password, int term, int max, vector<Copy> borrowed, vector<Copy> reserved);
	
	//Accessors
	int getTerm();
	int getMaxCopies();
	vector<Copy>& getBorrowedBookList();
	vector<Copy>& getReserved();
	int getPenalties();

	//Mutators
	void setTerm(int term);
	void setMaxCopies(int max);
	void setBorrowed(vector<Copy> borrowed);
	void setReserved(vector<Copy> reserved);
	void setPenalties(int penalties);

	//Overloaded Operators
	ostream& operator<<(ostream& out);
	istream& operator>>(istream& in);
	bool operator==(Reader& r);

	//Readers may have penalties
	bool penalty();
};

