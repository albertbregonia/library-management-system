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
		if (c == 32 || c == s[s.length()-1]) {
			if(!temp.empty())
				v.push_back(temp);
			temp = "";
		}
		else
			temp += c;
	return v;
}

//Returns the int of the book in the database given an ID
int Database::getBookByID(int id) {
	int index = -1;
	for (int i = 0; i < books.size(); i++)
		if (books.at(i).getID() == id)
			index = i;
	return index;
}

//Loads all the books from the database file 'book.txt'
bool Database::loadBooks() {
	fstream bookData("data\\book.txt");
	Book b = Book();
	if (bookData.is_open())
		while (!bookData.eof())
			b >> bookData;
	bookData.close();
	return Database::getBooks().size() > 0;
}

//Loads all the student accounts from the database file 'student.txt'
bool Database::loadStudents() {
	fstream studentData("data\\student.txt");
	Student s = Student();
	if (studentData.is_open())
		while (!studentData.eof())
			s >> studentData;
	studentData.close();
	return Database::getStudents().size() > 0;
}

//Save current data into the databases 'book.txt' and 'student.txt'
void Database::save() {
	ofstream studentFile("data\\student.txt");
	ofstream bookFile("data\\book.txt");
	if (studentFile.is_open() && bookFile.is_open()) {
		for (Student s : students)
			s << studentFile;
		for (Book b : books)
			b << bookFile;
	}
	else
		cout << "Error writing to database files! Please resolve this issue or contact a system administrator." << endl;
	studentFile.close();
	bookFile.close();
}