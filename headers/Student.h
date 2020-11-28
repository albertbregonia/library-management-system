//Instantiation of Student Object

#pragma once
#include "Reader.h"

class Student : public Reader {
public:
	//Constructors
	Student();
	Student(string username, string password, int term, int max, vector<Copy> borrowed, vector<Copy> reserved);
};