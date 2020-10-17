//Albert Bregonia 10/16

#include <iostream>
#include <istream>
#include <string>
using namespace std;

class UserAuthentication {
public:
	static bool signup(istream& in);
	static bool login(istream& in);
	static bool success(string& username, string& password); //pass by reference for memory efficiency
};