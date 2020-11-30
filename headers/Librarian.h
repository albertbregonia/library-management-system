#pragma once
#include "User.h"
class Librarian : public User {
public:
	//Constructor
	Librarian();
	Librarian(string username, string password);
	void add_book();//add book information
	void delet_book();//delete the book information
	void search_user();//search the user
	void add_user(User* U);//add the user
	void delet_user(User* U, Reader* r);//delete the user
};

