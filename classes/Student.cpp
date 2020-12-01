#include <iostream>
#include "Student.h"
#include "Database.h"

//Constructors
Student::Student(): Reader() {}

Student::Student(string username, string password, int term, int max, vector<Copy*> borrowed, vector<Copy*> reserved): 
	Reader(username, password, term, max, borrowed, reserved) {}