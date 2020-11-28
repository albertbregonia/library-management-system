#pragma once
#include "Student.h"

class Teacher : public Student
{
private:
	Reader info;
public:
	//Constructors
	Teacher();
	Teacher(string username, string password, int term, int max, vector<Book> borrowed, vector<Book> reserved);
};

