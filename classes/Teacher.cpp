#include "Teacher.h"

//Default Constructor - 50 day borrow period, 10 max books
Teacher::Teacher():
	info(Reader("none", "none", 50, 10, vector<Book>(), vector<Book>())) {}

//Parameterized Constructor
Teacher::Teacher(string username, string password, int term, int max, vector<Book> borrowed, vector<Book> reserved) :
	info(Reader(username, password, term, max, borrowed, reserved)) {}
