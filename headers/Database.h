//Albert Bregonia 10/16

#pragma once
#include <vector>
#include "Book.h"
#include "Student.h"

//Database Functions and Extra Utilities
class Database {
private:
	static vector<Student> students;
	static vector<Book> books;
public:
	static vector<Student>& getStudents();
	static vector<Book>& getBooks();
	static int getBookByID(int id);
	static bool loadBooks();
	static bool loadStudents();
	static void save();
	static vector<string> split(string s);
};