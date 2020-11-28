#include "Teacher.h"

//Default Constructor - 50 day borrow period, 10 max books
Teacher::Teacher():
	Reader("none", "none", 50, 10, vector<Copy>(), vector<Copy>()) {}

//Parameterized Constructor
Teacher::Teacher(string username, string password, int term, int max, vector<Copy> borrowed, vector<Copy> reserved) :
	Reader(username, password, term, max, borrowed, reserved) {}
