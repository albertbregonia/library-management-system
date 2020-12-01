#include "Database.h"
#include "Display.h"
#include <iostream>
#include <string>
#include <fstream>

//Initialize Static Variables
vector<Book> Database::books = vector<Book>(); //Types of Books
vector<Reader> Database::readers = vector<Reader>(); //Reader - Student/Teacher
vector<Copy> Database::copies = vector<Copy>(); //Books you can Borrow
vector<Librarian> Database::admins = vector<Librarian>(); //Admin
int Database::partition = 0;

//Accessors
int Database::getPartitioner() { return partition; }
vector<Reader>& Database::getReaders() { return readers; }
vector<Book>& Database::getBooks() { return books; }
vector<Copy>& Database::getCopies() { return copies; }
vector<Librarian>& Database::getAdmins() { return admins; }

//Mutator
void Database::setPartitioner(int i) { partition = i; }

//Startup
bool Database::loadBooks() { //Loads all the books from the database file 'book.txt' and 'copies.txt'
	//Load Types of Books
	fstream bookData("data\\book.txt");
	Book b = Book();
	if (bookData.is_open())
		while (!bookData.eof()) {
			bookData >> b;
			if (b.getTitle() != "title") //ensure a real 'book' is read in
				books.push_back(b);
		}
	bookData.close();
	//Load Copies
	fstream copyData("data\\copy.txt");
	Copy c = Copy();
	if (copyData.is_open())
		while (!copyData.eof()) {
			copyData >> c;
			if (c.getID() != -2) //ensure a real 'copy' is read in
				copies.push_back(c);
		}
	copyData.close();
	return Database::books.size() > 0 && Database::copies.size() > 0;
}

bool Database::loadAccounts() {
	//Loads all the accounts from the database files 'admin.txt', 'student.txt', 'teacher.txt'
	fstream studentFile("data\\student.txt");
	fstream teacherFile("data\\teacher.txt");
	fstream adminFile("data\\admin.txt");
	Reader r = Reader();
	Librarian l = Librarian();
	if (studentFile.is_open() && teacherFile.is_open() && adminFile.is_open()) {
		while (!studentFile.eof()) { //load in readers
			studentFile >> r;
			if (r.getUsername() != "none") //ensure a real user is read in
				readers.push_back(r);
		}
		partition = readers.size() - 1; //save index of where students end in the vector
		while (!teacherFile.eof()) { //load in teachers
			teacherFile >> r;
			if (r.getUsername() != "none") //ensure a real user is read in
				readers.push_back(r);
		}
		while (!adminFile.eof()) { //load in admins
			adminFile >> l;
			if (l.getUsername() != "admin") //ensure a real admin account is read in, nothing default
				admins.push_back(l);
		}
	}
	teacherFile.close();
	studentFile.close();
	adminFile.close();
	return readers.size() > 0 && admins.size() > 0;
}

void Database::save() {
	//Save current data into the databases
	ofstream studentFile("data\\student.txt");
	ofstream teacherFile("data\\teacher.txt");
	ofstream bookFile("data\\book.txt");
	ofstream copyFile("data\\copy.txt");
	ofstream libFile("data\\admin.txt");
	if (studentFile.is_open() && teacherFile.is_open() && bookFile.is_open() && copyFile.is_open() && libFile.is_open()) {
		//Save Books
		for (Book b : books)
			bookFile << b;
		for (Copy c : copies)
			copyFile << c;
		//Save Accounts
		for (int i = 0; i < readers.size(); i++)
			if (i <= partition) //students
				studentFile << readers[i];
			else //teachers
				teacherFile << readers[i];
		for (Librarian l : admins)
			libFile << l;
	}
	else
		cout << "Error writing to database files! Please resolve this issue or contact a system administrator." << endl;
	studentFile.close();
	teacherFile.close();
	bookFile.close();
	copyFile.close();
	libFile.close();
}

//============ FUNCTIONS ALL USERS CAN DO ============// 

//Option 1
void Database::searchBooks(istream& in) {
	//User Input To Search By Selected Key
	int choice;
	cout << "Search By: " << endl;
	string keys[] = { "ISBN", "Title", "Author", "Category" };
	for (int i = 0; i < 4; i++)
		cout << "\t " << i << " - " << keys[i] << endl;
	cout << endl << "Selection: ";
	in >> choice;
	cout << endl;
	Display::border();

	//Search
	string key;
	vector<totalBookInfo> popularity;
	bool found = false;
	switch (choice) {
	case 0: //ISBN Search
		cout << "Enter an ISBN to search for: ";
		in >> key;
		cout << endl;
		Display::border();
		for (Book b : Database::getBooks())
			if (b.getISBN() == key) { //Find book with ISBN
				cout << b; //Print Book Info
				cout << "***IDs: ";
				for (Copy c : Database::getCopies()) //Find all IDs of that Book
					if (c.getBook()->getISBN() == key)
						cout << c.getID() << " ";
				cout << endl << endl;
				return; //There is only 1 ISBN per book
			}
		cout << "No Results." << endl;
		break;
	case 1: //Title Search
		cout << "Enter a title to search for: ";
		getline(in >> ws, key); // 'in >> ws' is used to include whitespace
		key = toLower(key); //Converted to lowercase to ignore capitals
		cout << endl;
		Display::border();
		for (Book b : Database::getBooks())
			if (toLower(b.getTitle()).find(key) != string::npos) { //Find book with title or string in title
				if (!found) //At least 1 result
					found = true;
				cout << b; //Print Book Info
				string t = b.getTitle();
				cout << "***IDs: ";
				for (Copy c : Database::getCopies()) //Find all IDs of that Book
					if (c.getBook()->getTitle() == t)
						cout << c.getID() << " ";
				cout << endl << endl;
			}
		if(!found)
			cout << "No Results." << endl;
		break;
	case 2: //Author Based Search
		cout << "Enter an author to search for: ";
		getline(in >> ws, key);
		key = toLower(key);
		cout << endl;
		Display::border();
		for (Book b : Database::getBooks())
			if (toLower(b.getAuthor()).find(key) != string::npos) { //Find book with title or string in title
				if (!found) //At least 1 result
					found = true;
				totalBookInfo temp; //Save Book, IDs and Reserve Count for each copy
				temp.book = b;
				string t = b.getTitle();
				temp.ids = "***IDs: ";
				for (Copy c : Database::getCopies()) //Find all IDs of that Book
					if (c.getBook()->getTitle() == t) {
						temp.ids += to_string(c.getID());
						temp.ids += " ";
						temp.numReserves += c.getReservers().size();
					}
				popularity.push_back(temp); //Add to list of books to sort based on popularity
			}
		if (found){
			sort(popularity); //selection sort based on number of reserves
			for (totalBookInfo i : popularity) //Print books
				cout << i.book << i.ids << endl << endl;
		}
		else
			cout << "No Results." << endl;
		break;
	case 3: //Category Based Search
		cout << "Enter a category to search for: ";
		getline(in >> ws, key);
		key = toLower(key);
		cout << endl;
		Display::border();
		for (Book b : Database::getBooks())
			if (toLower(b.getCategory()).find(key) != string::npos) { //Find book with title or string in title
				if (!found) //At least 1 result
					found = true;
				totalBookInfo temp; //Save Book, IDs and Reserve Count for each copy
				temp.book = b;
				string t = b.getTitle();
				temp.ids = "***IDs: ";
				for (Copy c : Database::getCopies()) //Find all IDs of that Book
					if (c.getBook()->getTitle() == t) {
						temp.ids += to_string(c.getID());
						temp.ids += " ";
						temp.numReserves += c.getReservers().size();
					}
				popularity.push_back(temp); //Add to list of books to sort based on popularity
			}
		if (found) {
			sort(popularity); //selection sort based on number of reserves
			for (totalBookInfo i : popularity) //Print books
				cout << i.book << i.ids << endl << endl;
		}
		else
			cout << "No Results." << endl;
		break;
	default: //Invalid Inputs
		cout << "Invalid Input." << endl;
		Display::border();
		break;
	}
}

//Option 7 - Change Password
void Database::changePassword(istream& in, User& u) {
	string current;
	cout << "Please input your current password: ";
	in >> current;
	if (current == u.getPassword()) {
		cout << "Verification Successful. Please enter in your new desired password: ";
		cin >> current;
		u.setPassword(current);
		cout << "Updated Password Successfully." << endl;
	}
	else
		cout << "Verification Failed. Unable to change password." << endl;
}

//============ UTILITY FUNCTIONS ============// 
//- they allow for searching through the database

//splits a string delimited by spaces and returns a vector<string> with data given from said string
vector<string> Database::split(string s) {
	vector<string> v;
	string temp("");
	for (char c : s)
		if (c == 32 || c == s[s.length() - 1]) {
			if (c == s[s.length() - 1] && c > 32)
				temp += c;
			if (!temp.empty())
				v.push_back(temp);
			temp = "";
		}
		else
			temp += c;
	return v;
}

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

//Converts strings to lowercase
string Database::toLower(string s) {
	string temp = "";
	for (char c : s)
		temp += tolower(c);
	return temp;
}

//Selection sort based on popularity
void Database::sort(vector<totalBookInfo>& v) {
	for (int i = 0; i < v.size() - 1; i++) {
		int index = i;
		for (int k = i + 1; k < v.size(); k++)
			if (v[k].numReserves > v[index].numReserves)
				index = k;
		swap(v[i], v[index]);
	}
}