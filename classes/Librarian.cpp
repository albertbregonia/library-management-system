#include "Librarian.h"

//Constructor
Librarian::Librarian() : User("admin", "admin") {}

Librarian::Librarian(string username, string password) : User(username, password) {}
