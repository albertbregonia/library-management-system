//Instantiation of Student Object

#include <string>
#include "Book.h"

using namespace std;

class Student {

private:
	string username;
	string password;
	int term; //borrow period
	int max; //max # of copies a student is allowed to keep
	Book borrowed[]; //Array of borrowed items; Array is used instead of a vector for memory efficiency

public:


};