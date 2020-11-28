//Albert Bregonia 10/16

#pragma once
#include <vector>
#include "Book.h"
#include "Student.h"
#include "Copy.h"

//Database Functions and Extra Utilities
class Database {
private:
	static vector<Reader> readers;
	static vector<Book> books;
	static vector<Copy> copies;
public:
	static vector<Reader>& getReaders();
	static vector<Book>& getBooks();
	static vector<Copy>& getCopies();
	static int getBookByID(int id);
	static bool loadBooks();
	static bool loadStudents();
	static void save();
	static vector<string> split(string s);
};
