//Instantiation of Book Object

#pragma once
#include <string>
using namespace std;

class Book {

private:
	long ISBN;
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
	Book(long ISBN, string title, string author, string category, int id, string reader, long start, long end);
	void operator<<(const fstream& file) const; //read object in
	void operator>>(const fstream& file) const; //write object out

	//Accessors
	long getISBN();
	string getTitle();
	string getAuthor();
	string getCategory();
	int getID();
	string getBorrower();
	long getStartDate();
	long getExpirationDate();

	//Mutators
	void setISBN(long ISBN);
	void setTitle(string title);
	void setAuthor(string author);
	void setCategory(string category);
	void setID(int id);
	void setBorrower(string reader);
	void setStartDate(long start);
	void setExpirationDate(long end);

	//Display
	void print();
};
