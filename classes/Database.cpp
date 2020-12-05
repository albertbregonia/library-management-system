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
bool Database::loadBooks() { 
	//Loads all the books from the database file 'book.txt' and 'copies.txt'

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
	//Ensure count is correct
	for (int i = 0; i < books.size(); i++)
		books[i].setCount(getAllCopiesByISBN(books[i].getISBN()).size());
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

//Option 1 
void Database::searchBooks(istream& in) {
	//User Input To Search By Selected Key
	int choice;
	cout << "Search By: " << endl;
	string keys[] = { "ISBN", "Title", "Author", "Category" };
	for (int i = 0; i < 4; i++)
		cout << "\t " << i << " - " << keys[i] << endl;
	cout << "\t -1 - Cancel" << endl;
	cout << endl << "Selection: ";
	bool error;
	do { //Handle invalid inputs
		string input;
		getline(in >> ws, input);
		try {
			choice = stoi(input);
			error = false;
		}
		catch (...) {
			error = true;
			cout << "Invalid Input. Please try again." << endl << endl;
		}
	} while (error);
	cout << endl;
	Display::border();

	//Search
	string key;
	vector<totalBookInfo> popularity;
	bool found = false;

	if (choice >= 0 && choice < 4) { //User Input
		cout << "Enter [" << keys[choice] << "] to search for: ";
		getline(in >> ws, key); // 'in >> ws' is used to include whitespace
		key = toLower(key); 
		cout << endl;
		Display::border();
	}
	switch (choice) {
	case -1: //Cancel
		cout << "Returning to main menu..." << endl;
		break;
	case 0: //ISBN Search
		for (Book b : books)
			if (b.getISBN() == key) { //Find book with ISBN
				cout << b; //Print Book Info
				cout << "***IDs: ";
				for (Copy* c : getAllCopiesByISBN(b.getISBN())) //Find all IDs of that Book
					cout << c->getID() << " ";
				cout << endl << endl;
				return; //There is only 1 ISBN per book
			}
		cout << "No Results." << endl;
		break;
	case 1: //Title Search
		for (Book b : books)
			if (toLower(b.getTitle()).find(key) != string::npos) { //Find book with title or string in title
				if (!found) //At least 1 result
					found = true;
				cout << b; //Print Book Info
				cout << "***IDs: ";
				for (Copy* c : getAllCopiesByTitle(b.getTitle())) //Find all IDs of that Book and print
					cout << c->getID() << " ";
				cout << endl << endl;
			}
		if(!found)
			cout << "No Results." << endl;
		break;
	case 2: //Author Based Search
	case 3: //Category Based Search - As choices 2 and 3 carry out the same algorithm an if statement is used to simplify code
		for (int z=0; z<books.size(); z++)
			if ((choice == 2 && toLower(books[z].getAuthor()).find(key) != string::npos) || //Find book with author or string in author if 2
				(choice == 3 && toLower(books[z].getCategory()).find(key) != string::npos)) { //Find book with category or string in category if 3
				if (!found) //At least 1 result
					found = true;
				totalBookInfo temp; //Save Book, IDs and Reserve Count for each copy
				temp.book = &books[z];
				temp.ids = "***IDs: ";
				for (Copy* c : getAllCopiesByTitle(books[z].getTitle()))//Find all IDs of that Book
					temp.ids += to_string(c->getID()) + " "; //update totalBookInfo to sort by popularity
				temp.numReserves = getBookPopularity(books[z].getISBN());
				popularity.push_back(temp); //Add to list of books to sort based on popularity
			}
		if (found) {
			sort(popularity); //selection sort based on number of reserves
			for (totalBookInfo i : popularity) //Print books
				cout << *i.book << i.ids << endl << endl;
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



//============ TRAVERSAL FUNCTIONS ============// 
// Anything that returns an index, returns -1 if nothing was found

//Returns a vector of all IDs in the database sorted least to greatest
vector<int> Database::getAllIDs() {
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

//Returns vector of pointers to copies in database based on ISBN
vector<Copy*> Database::getAllCopiesByISBN(string ISBN) {
	vector<Copy*> list;
	for (int i = 0; i < copies.size(); i++) //find all copies of a book
		if (copies[i].getBook()->getISBN() == ISBN)
			list.push_back(&copies[i]);
	return list;
}

//Returns vector of pointers to copies in database based on title
vector<Copy*> Database::getAllCopiesByTitle(string title) {
	vector<Copy*> list;
	for (int i = 0; i < copies.size(); i++) //find all copies of a book
		if (toLower(copies[i].getBook()->getTitle()) == toLower(title)) //lowercase for better results
			list.push_back(&copies[i]);
	return list;
}

//Returns a vector of pointers to top rated books
vector<Book*> Database::getTopRated() {
	//id parameter: range of 0-3;
	vector<Book*> list;
	for (int i = 0; i < books.size(); i++)
		list.push_back(&books[i]);
	//selection sort, greatest to least
	for (int i = 0; i < list.size() - 1; i++) { 
		int index = i;
		for (int z = i + 1; z < list.size(); z++)
			if (list[z]->getFavor() > list[index]->getFavor())
				index = z;
		swap(list[index], list[i]);
	}
	return list;
}

//Returns the index of the copy in the database given an ID
int Database::getCopyByID(int id) {
	for (int i = 0; i < copies.size(); i++)
		if (copies[i].getID() == id)
			return i;
	return -1;
}

//Returns the index of the book in the database given an ISBN
int Database::getBookByISBN(string ISBN) {
	for (int i = 0; i < books.size(); i++)
		if (books[i].getISBN() == ISBN)
			return i;
	return -1;
}

//Returns index of the reader in the database given a username
int Database::getReaderByUsername(string username) {
	for (int i = 0; i < readers.size(); i++)
		if (toLower(readers[i].getUsername()) == toLower(username))
			return i;
	return -1;
}

//Returns index of the librarian in the database given a username
int Database::getAdminByUsername(string username) {
	for (int i = 0; i < admins.size(); i++)
		if (toLower(admins[i].getUsername()) == toLower(username))
			return i;
	return -1;
}

//Returns the index of the user in the reserve list of a copy given a username and copy
int Database::getUserInReservers(Copy& c, string username) {
	for (int i = 0; i < c.getReservers().size(); i++)
		if (toLower(c.getReservers()[i]) == toLower(username))
			return i;
	return -1;
}

//Returns the index of the ID in the borrowed list of a user given an ID
int Database::getCopyInBorrowedList(Reader& r, int id) {
	for (int i = 0; i < r.getBorrowedBookList().size(); i++)
		if (r.getBorrowedBookList()[i]->getID() == id)
			return i;
	return -1;
}

//Returns the index of the ID in the reserve list of a user given an ID
int Database::getCopyInReserveList(Reader& r, int id) {
	for (int i = 0; i < r.getReserved().size(); i++)
		if (r.getReserved()[i]->getID()==id)
			return i;
	return -1;
}

//Deletes reserver from both the queue of dates/usernames of the copy and the user's reserved vector
void Database::deleteReserver(Reader& r, Copy& c, int pos) {
	if (pos >= 0 && pos < c.getReservers().size() && getCopyInReserveList(r, c.getID()) >= 0) {
		c.getReservers().erase(c.getReservers().begin() + pos);
		c.getReserveDates().erase(c.getReserveDates().begin() + pos);
		r.getReserved().erase(r.getReserved().begin() + getCopyInReserveList(r, c.getID()));
	}
}

//Returns the total number of reserves on all copies of a book
int Database::getBookPopularity(string ISBN) {
	int pop = 0;
	for (Copy* c : getAllCopiesByISBN(ISBN))
		pop += c->getReservers().size();
	return pop;
}



//============ UTILITY FUNCTIONS ============//

int Database::inputHandler(istream& in) {
	bool error;
	int num;
	do { //Handle invalid inputs when inputting an integer and a string is given
		string input;
		getline(in>>ws, input);
		try {
			num = stoi(input);
			error = false;
		}
		catch (...) {
			error = true;
			cout << "Invalid Input. Please try again. \n\nSelection: ";
		}
	} while (error);
	return num;
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

//Converts strings to lowercase as well as returns the original string so that string class functions can still be used
string Database::toLower(string s) {
	string temp = "";
	for (char c : s)
		temp += tolower(c);
	return temp;
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