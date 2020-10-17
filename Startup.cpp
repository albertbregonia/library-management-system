//Albert Bregonia 10/16

#include <iostream>
#include <fstream>
#include "Startup.h"

//Initialize Static Variables
vector<Book> Startup::books = vector<Book>();
vector<Student> Startup::students = vector<Student>();

vector<Student> Startup::getStudents() { return students; }
vector<Book> Startup::getBooks() { return books; }

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
Book* Startup::getBookByID(int id) {
	for (Book b : books)
		if (b.getID() == id)
			return &b;
}

bool Startup::loadBooks() {
	fstream bookData("data\\book.txt");
	long ISBN, start, end;
	string title, author, category, reader, line;
	int id;
	if (bookData.is_open())
		for (int i = 0; getline(bookData, line); i++) {
			switch (i) {
				case 0:
					ISBN = 1; //as of 10/17 for some reason this always throws an error although it is given a valid number???
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

bool Startup::loadStudents() {
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