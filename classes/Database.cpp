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

//============ USERS FUNCTIONS ============// 

//Option 1 ***** cleanup
void Database::searchBooks(istream& in) {
	//User Input To Search By Selected Key
	int choice;
	cout << "Search By: " << endl;
	string keys[] = { "ISBN", "Title", "Author", "Category" };
	for (int i = 0; i < 4; i++)
		cout << "\t " << i << " - " << keys[i] << endl;
	cout << "\t -1 - Cancel" << endl;
	cout << endl << "Selection: ";
	in >> choice;
	cout << endl;
	Display::border();

	//Search
	string key;
	vector<totalBookInfo> popularity;
	bool found = false;

	if (choice >= 0 && choice < 4) { //User Input
		cout << "Enter [" << keys[choice] << "] to search for: ";
		getline(in >> ws, key); // 'in >> ws' is used to include whitespace
		key = toLower(key); //lowercase for better results
		cout << endl;
		Display::border();
	}
	switch (choice) {
	case -1:
		break;
	case 0: //ISBN Search
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
		for (Book b : Database::getBooks())
			if (toLower(b.getTitle()).find(key) != string::npos) { //Find book with title or string in title
				if (!found) //At least 1 result
					found = true;
				cout << b; //Print Book Info
				string t = b.getTitle();
				cout << "***IDs: ";
				for (Copy c : Database::getCopies()) //Find all IDs of that Book and print
					if (c.getBook()->getTitle() == t)
						cout << c.getID() << " ";
				cout << endl << endl;
			}
		if(!found)
			cout << "No Results." << endl;
		break;
	case 2: //Author Based Search
	case 3: //Category Based Search - As choices 2 and 3 carry out the same algorithm an if statement is used to simplify code
		for (Book b : Database::getBooks())
			if ((choice == 2 && toLower(b.getAuthor()).find(key) != string::npos) || //Find book with author or string in author if 2
				(choice == 3 && toLower(b.getCategory()).find(key) != string::npos)) { //Find book with category or string in category if 3
				if (!found) //At least 1 result
					found = true;
				totalBookInfo temp; //Save Book, IDs and Reserve Count for each copy
				temp.book = b;
				string t = b.getTitle();
				temp.ids = "***IDs: ";
				for (Copy c : Database::getCopies()) //Find all IDs of that Book
					if (c.getBook()->getTitle() == t) {
						temp.ids += to_string(c.getID()) + " "; //update totalBookInfo to sort by popularity
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



//splits a string delimited by spaces and returns a vector<string> with data given from said string
vector<string> Database::split(string s) {
	vector<string> v;
	string temp("");
	for (char c : s)
		if (c == 32 || c == s[s.length() - 1]) {
			if (c == s[s.length() - 1] && c > 32) //if the last character is a valid character
				temp += c;
			if (!temp.empty())
				v.push_back(temp);
			temp = "";
		}
		else
			temp += c;
	return v;
}

//Returns a vector of all IDs in the database sorted least to greatest
vector<int> Database::getAllCopyIDs() {
	vector<int> ids;
	for (Copy c : copies) //load in all IDs
		ids.push_back(c.getID());
	//selection sort to sort IDs
	for (int x = 0; x < ids.size() - 1; x++) {
		int index = x;
		for (int y = x + 1; y < ids.size(); y++)
			if (ids[y] < ids[index]) //least to greatest
				index = y;
		swap(ids[x], ids[index]);
	}
	return ids;
}

//Returns the index of the book in the database given an ISBN
int Database::getBookByISBN(string ISBN) {
	int index = -1;
	for (int i = 0; i < books.size(); i++)
		if (books.at(i).getISBN() == ISBN) {
			index = i;
			break;
		}
	return index;
}

//Returns the index of the copy in the database given an ID
int Database::getCopyByID(int id) {
	int index = -1;
	for (int i = 0; i < copies.size(); i++)
		if (copies.at(i).getID() == id) {
			index = i;
			break;
		}
	return index;
}

//Returns index of the reader in the database given a username
int Database::getReaderByUsername(string username) {
	int index = -1;
	for (int i = 0; i < readers.size(); i++)
		if (readers[i].getUsername() == username) {
			index = i;
			break;
		}
	return index;
}

//Returns index of the librarian in the database given a username
int Database::getAdminByUsername(string username) {
	int index = -1;
	for (int i = 0; i < admins.size(); i++)
		if (readers[i].getUsername() == username) {
			index = i;
			break;
		}
	return index;
}

//Converts strings to lowercase as well as returns the original string so that string class functions can still be used
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