//Albert Bregonia 10/16

#include <iostream>
#include <fstream>
#include "Database.h"

//Initialize Static Variables
vector<Book> Database::books = vector<Book>();
vector<Student> Database::students = vector<Student>();

vector<Student>& Database::getStudents() { return students; }
vector<Book>& Database::getBooks() { return books; }

//splits a string delimited by spaces and returns a vector<string> with data given from said string
vector<string> Database::split(string s) {
	vector<string> v;
	string temp("");
	for (char c : s)
		if (c == 32) {
			v.push_back(temp);
			temp = "";
		}
		else
			temp += c;
	return v;
}

//Returns the book given an ID
Book* Database::getBookByID(int id) {
	for (Book b : books)
		if (b.getID() == id)
			return &b;
}

bool Database::loadBooks() {
	fstream bookData("data\\book.txt");
	Book b = Book();
	if (bookData.is_open())
		while (!bookData.eof())
			b >> bookData;
	bookData.close();
	return Database::getBooks().size() > 0;
}

bool Database::loadStudents() {
	fstream studentData("data\\student.txt");
	Student s = Student();
	if (studentData.is_open())
		while (!studentData.eof())
			s >> studentData;
	studentData.close();
	return Database::getStudents().size()>0;
}

//Save current data into the databases 'book.txt' and 'student.txt'
void Database::save() {
	ofstream file("data\\student.txt");
	if (file.is_open())
		for (Student s : students)
			s << file;
	else
		cout << "Error writing to database file, 'student.txt'! Please resolve this issue or contact a system administrator." << endl;
	file.close();
}