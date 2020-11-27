#pragma once
#include "Student.h"
//A teacher can do everything that a student can, 
//only difference is the default constructor
class Teacher : public Student
{
private:
	Student attributes;
public:
	Teacher();
	Teacher(string username, string password, int term, int max, vector<Book> borrowed, vector<Book> reserved);
};

