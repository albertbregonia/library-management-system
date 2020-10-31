//Albert Bregonia 10/16

#include <iostream>
#include <fstream>
#include "Database.h"

//Initialize Static Variables
vector<Book> Database::books = vector<Book>();
vector<Student> Database::students = vector<Student>();

vector<Student> Database::getStudents() { return students; }
vector<Book> Database::getBooks() { return books; }

//splits a string delimited by spaces and returns a vector<string> with data given from said string
vector<string> split(string s) {
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
	string line;
	long start, end;
	string ISBN, title, author, category, reader;
	int id;
	if (bookData.is_open())
		for (int i = 0; getline(bookData, line); i++) {
			switch (i) {
				case 0:
					ISBN = line;
					break;
				case 1:
					title = line;
					break;
				case 2:
					author = line;
					break;
				case 3:
					category = line;
					break;
				case 4:
					id = stoi(line);
					break;
				case 5:
					reader = line;
					break;
				case 6:
					start = stol(line);
					break;
				case 7:
					end = stol(line);
					books.push_back(Book(ISBN, title, author, category, id, reader, start, end));
					break;
				default:
					i = -1;
			}
		}
	return bookData.is_open();
}

bool Database::loadStudents() {
	fstream studentData("data\\student.txt");
	string username, password;
	int term, max;
	string line;
	vector<Book> bookList;
	if (studentData.is_open())
		for (int i = 0; getline(studentData, line); i++)
			switch (i) {
				case 0:
					username = line;
					break;
				case 1:
					password = line;
					break;
				case 2:
					term = stoi(line);
					break;
				case 3:
					max = stoi(line);
					break;
				case 4:
					bookList.clear();
					for (string id : split(line))
						books.push_back(*getBookByID(stoi(id)));
					students.push_back(Student(username, password, term, max, bookList));
					break;
				default:
					i = -1;
			}
	return studentData.is_open();
}

//Save current data into the databases 'book.txt' and 'student.txt'
void Database::save() {
	fstream file("data\\student.txt");
	if (file.is_open())
		for (Student s : students)
			s << file;
	else
		cout << "Error writing to database file, 'student.txt'! Please resolve this issue or contact a system administrator." << endl;
	file.close();
}