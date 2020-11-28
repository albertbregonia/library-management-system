#pragma once
#include "User.h"
class Librarian : public User {
private:
	User login;
public:
	//Constructor
	Librarian();
	Librarian(string username, string password);
	//Accessor
	User getLogin();
	//Mutator
	void setLogin(User login);
};

