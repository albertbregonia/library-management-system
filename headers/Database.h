//Albert Bregonia 10/16

#pragma once
#include "Date.h"
#include "Reader.h"
#include "Librarian.h"
#include <vector>
#include <string>
using namespace std;

//Database Functions and Extra Utilities
class Database {
private:
	static vector<Reader> readers;
	static vector<Librarian> admins; //Administrative Accounts
	static vector<Book> books; //Types of Books
	static vector<Copy> copies; //Virtual Books
	//Defined to Sort Books based on popularity
	struct totalBookInfo {
		Book book = Book();
		string ids = "";
		int numReserves = 0;
	};
public:
	//Accessors
	static vector<Reader>& getReaders();
	static vector<Librarian>& getAdmins();
	static vector<Book>& getBooks();
	static vector<Copy>& getCopies();

	//Utility
	static int getCopyByID(int id);
	static int getBookByISBN(string ISBN);
	static vector<string> split(string s);
	static string toLower(string s);
	static void sort(vector<totalBookInfo>& v);

	//Traverse Database
	static bool loadBooks();
	static bool loadAccounts();
	static void save();

	//User Actions
	static void searchBooks(istream& in);
	static void changePassword(istream& in, User& u);
};
