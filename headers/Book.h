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
	string index;
	int count;
	int favor; //1-5 scale
public:
	//Constructors
	Book();
	Book(string ISBN, string title, string author, string category, string index, int count, int favor);

	//Accessors
	string getISBN();
	string getTitle();
	string getAuthor();
	string getCategory();
	string getIndex();
	int getCount();
	int getFavor();

	//Mutators
	void setISBN(string ISBN);
	void setTitle(string title);
	void setAuthor(string author);
	void setCategory(string category);
	void setIndex(string i);
	void setCount(int i);
	void setFavor(int i);

	//Overloaded Operators
	ostream& operator<<(ostream& out) const;
	istream& operator>>(istream& in);
};
