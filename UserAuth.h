//Albert Bregonia 10/16

#include <iostream>
#include <istream>
#include <string>
#include "Student.h"
using namespace std;

class UserAuthentication {
public:
	static bool signup(istream& in);
	static int login(istream& in);
};