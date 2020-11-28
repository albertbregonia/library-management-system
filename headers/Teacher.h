#pragma once
#include "Reader.h"

class Teacher : public Reader {
public:
	//Constructors
	Teacher();
	Teacher(string username, string password, int term, int max, vector<Copy> borrowed, vector<Copy> reserved);
};

