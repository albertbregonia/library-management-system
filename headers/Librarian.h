#pragma once
#include "User.h"
class Librarian : public User {
public:
	//Constructor
	Librarian();
	Librarian(string username, string password);

	void deleteBook(istream& in);
	void deleteUser(istream& in);
	void searchUsers(istream& in);
	void addBook(istream& in);
	void addUser(istream& in);
};

