#include "Teacher.h"

//Default Constructor
Teacher::Teacher():
	attributes(Student("none", "none", 50, 10, vector<Book>(), vector<Book>()))
{}

//Parameterized Constructor
Teacher::Teacher(string username, string password, int term, int max, vector<Book> borrowed, vector<Book> reserved) :
	attributes(Student(username, password, term, max, borrowed, reserved))
{}
