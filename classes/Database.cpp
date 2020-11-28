#include "Database.h"
#include <iostream>
#include <fstream>

//Initialize Static Variables
vector<Book> Database::books = vector<Book>();
vector<Reader> Database::readers = vector<Reader>();
vector<Copy> Database::copies = vector<Copy>();
vector<Librarian> Database::admins = vector<Librarian>();

//Accessors
vector<Reader>& Database::getReaders() { return readers; }
vector<Book>& Database::getBooks() { return books; }
vector<Copy>& Database::getCopies() { return copies; }
vector<Librarian>& Database::getAdmins() { return admins; }

//splits a string delimited by spaces and returns a vector<string> with data given from said string
vector<string> Database::split(string s) {
	vector<string> v;
	string temp("");
	for (char c : s)
		if (c == 32 || c == s[s.length()-1]) {
			if(!temp.empty())
				v.push_back(temp);
			temp = "";
		}
		else
			temp += c;
	return v;
}

//============ UTILITY FUNCTIONS ============// 
//- they allow for searching through the database

//Returns the index of the copy in the database given an ID
int Database::getCopyByID(int id) {
	int index = -1;
	for (int i = 0; i < copies.size(); i++)
		if (copies.at(i).getID() == id)
			index = i;
	return index;
}

//Returns the index of the book in the database given an ISBN
int Database::getBookByISBN(string ISBN) {
	int index = -1;
	for (int i = 0; i < books.size(); i++)
		if (books.at(i).getISBN() == ISBN)
			index = i;
	return index;
}

//Loads all the books from the database file 'book.txt' and 'copies.txt'
bool Database::loadBooks() {
	//Load Types of Books
	fstream bookData("data\\book.txt");
	Book b = Book();
	if (bookData.is_open())
		while (!bookData.eof()) {
			b >> bookData;
			if(b.getTitle()!="title") //ensure a real 'book' is read in
				books.push_back(b);
		}
	bookData.close();
	//Load Copies
	fstream copyData("data\\copy.txt");
	Copy c = Copy();
	if (copyData.is_open())
		while (!copyData.eof()) {
			c >> copyData;
			if(c.getID()!=-2) //ensure a real 'copy' is read in
				copies.push_back(c);
		}
	copyData.close();
	return Database::books.size() > 0 && Database::copies.size() > 0;
}

//Loads all the accounts from the database file 'reader.txt'
//- this was changed from 'student.txt' to incorporate teachers as well
bool Database::loadAccounts() {
	fstream readerFile("data\\reader.txt");
	fstream adminFile("data\\admin.txt");
	Reader r = Reader();
	Librarian l = Librarian();
	if (readerFile.is_open() && adminFile.is_open()) {
		while (!readerFile.eof()) { //load in readers
			r >> readerFile;
			if(r.getUsername()!="none") //ensure a real user is read in
				readers.push_back(r);
		}
		while (!adminFile.eof()) { //load in admins
			l >> adminFile;
			if (l.getUsername() != "admin") //ensure a real admin account is read in
				admins.push_back(l);
		}
	}
	readerFile.close();
	adminFile.close();
	return readers.size() > 0 && admins.size() > 0;
}

//Save current data into the databases 'book.txt' and 'student.txt'
void Database::save() {
	ofstream readerFile("data\\reader.txt");
	ofstream bookFile("data\\book.txt");
	ofstream copyFile("data\\copy.txt");
	ofstream libFile("data\\admin.txt");
	if (readerFile.is_open() && bookFile.is_open() && copyFile.is_open() && libFile.is_open()) {
		//Save Books
		for (Book b : books)
			b << bookFile;
		for (Copy c : copies)
			c << copyFile;
		//Save Accounts
		for (Reader r : readers)
			r << readerFile;
		for (Librarian l : admins)
			l << libFile;
	}
	else
		cout << "Error writing to database files! Please resolve this issue or contact a system administrator." << endl;
	readerFile.close();
	bookFile.close();
	copyFile.close();
	libFile.close();
}