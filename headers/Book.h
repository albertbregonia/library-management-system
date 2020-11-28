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

public:
	//Constructors
	Book();
	Book(string ISBN, string title, string author, string category);

	//Accessors
	string getISBN();
	string getTitle();
	string getAuthor();
	string getCategory();

	//Mutators
	void setISBN(string ISBN);
	void setTitle(string title);
	void setAuthor(string author);
	void setCategory(string category);

	//Overloaded Operators
	ostream& operator<<(ostream& out) const;
	istream& operator>>(istream& in);
};
