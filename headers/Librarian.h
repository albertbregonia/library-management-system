#pragma once
#include "User.h"
class Librarian : public User {
public:
	//Constructor
	Librarian();
	Librarian(string username, string password);

	void addBook(istream& in);
	void deleteBook(istream& in);
	void searchUsers(istream& in);
	void addUser(istream& in);
	void deleteUser(istream& in);
};

