//Albert Bregonia 10/16

#pragma once
#include "Date.h"
#include "Reader.h"
#include <vector>
#include <string>
using namespace std;

//Database Functions and Extra Utilities
class Database {
private:
	static vector<Reader> readers;
	static vector<Book> books; //Types of Books
	static vector<Copy> copies; //Virtual Books
public:
	static vector<Reader>& getReaders();
	static vector<Book>& getBooks();
	static vector<Copy>& getCopies();
	static int getCopyByID(int id);
	static int getBookByISBN(string ISBN);
	static bool loadBooks();
	static bool loadStudents();
	static void save();
	static vector<string> split(string s);
};
