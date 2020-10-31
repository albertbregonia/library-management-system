//Instantiation of Book Object

#pragma once
#include <string>
using namespace std;

class Book {

private:
	string ISBN;
	string title;
	string author;
	string category;
	int id; //Book ID
	string reader; //Borrower
	long start; //start date
	long end; //expiration date

public:
	//Constructors
	Book();
	Book(string ISBN, string title, string author, string category, int id, string reader, long start, long end);

	//Accessors
	string getISBN();
	string getTitle();
	string getAuthor();
	string getCategory();
	int getID();
	string getBorrower();
	long getStartDate();
	long getExpirationDate();

	//Mutators
	void setISBN(string ISBN);
	void setTitle(string title);
	void setAuthor(string author);
	void setCategory(string category);
	void setID(int id);
	void setBorrower(string reader);
	void setStartDate(long start);
	void setExpirationDate(long end);

	//Overloaded Operators
	ostream& operator<<(ostream& out) const;
	istream& operator>>(istream& in) const;
};
