#include "Librarian.h"

//Constructor
Librarian::Librarian() :
	login(User("admin", "admin")) {}

Librarian::Librarian(string username, string password) :
	login(User(username, password)) {}

//Accessor
User Librarian::getLogin() { return login; }

//Mutator
void Librarian::setLogin(User login) { this->login = login; }