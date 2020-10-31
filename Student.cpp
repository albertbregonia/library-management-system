#include "Student.h"
#include <iostream>

//Constructors
Student::Student(): 
	username("none"),
	password("none"),
	term(0),
	max(0),
	borrowed(vector<Book>())
{}
Student::Student(string username, string password, int term, int max, vector<Book> borrowed):
	username(username),
	password(password),
	term(term),
	max(max),
	borrowed(borrowed)
{}
//Accessors
string Student::getUsername() { return username; }
string Student::getPassword() { return password; }
int Student::getTerm() { return term; }
int Student::getMaxCopies() { return max; }
vector<Book> Student::getBorrowedBookList() { return borrowed; }

//Mutators
void Student::setUsername(string username) { this->username = username; }
void Student::setPassword(string password) { this->password = password; }
void Student::setTerm(int term) { this->term = term; }
void Student::setMaxCopies(int max) { this->max = max; }
void Student::setBorrowedBooks(vector<Book> borrowed) { this->borrowed = borrowed; }

//Overloaded Operators
ostream& Student::operator<<(ostream& out) const {
	return out;
}