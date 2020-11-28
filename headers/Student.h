//Instantiation of Student Object

#pragma once
#include <string>
#include <vector>
#include "Book.h"
#include "Date.h"
#include "Reader.h"

using namespace std;

class Student : public Reader {
private:
	Reader info;
public:
	//Constructors
	Student();
	Student(string username, string password, int term, int max, vector<Book> borrowed, vector<Book> reserved);
	//Accessor
	Reader getInfo();
	//Mutator
	Reader setInfo(Reader r);

	//Student Actions
	void borrowBooks(istream& in);
	void returnBooks(istream& in);
};