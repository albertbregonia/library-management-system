#include "User.h"

//Constructors
User::User() :
	username("none"),
	password("none")
{}

User::User(string username, string password) :
	username(username),
	password(password)
{}

//Accessors
string User::getUsername() { return username; }
string User::getPassword() { return password; }

//Mutators
void User::setUsername(string username) { this->username = username; }
void User::setPassword(string password) { this->password = password; }