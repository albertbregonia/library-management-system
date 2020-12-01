#include "Librarian.h"
#include "Database.h"
#include "UserAuth.h"
#include <iostream>

//Constructor
Librarian::Librarian() : User("admin", "admin") {}

Librarian::Librarian(string username, string password) : User(username, password) {}

//Option 2
void Librarian::addBook(istream& in) {
	cout << "Please enter in the Book Information." << endl;
	cout << "Please enter in the order of [ISBN - Title - Author - Catgeory - Index -  1 - 0 - End]:" << endl;
	cout << "'1' and '0' are the default 'Count' and 'Favor' attributes. \nIf this book already exists in the database it will adjusted accordingly." << endl;
	cout << "If this is a new book that has not been in the database, these are the default parameters." << endl << endl;
	cout << "Book Information:" << endl;
	Book b;
	b >> in;
	cout << endl;

	//create a New Copy of the book
	Copy c;
	vector<int> ids;
	for (Copy c : Database::getCopies()) //load in all IDs
		ids.push_back(c.getID());
	int index;
	for (int x = 0; x < ids.size() - 1; x++) { //selection sort to sort IDs
		index = x;
		for (int y = x + 1; y < ids.size(); y++)
			if (ids[y] < ids[index]) //least to greatest
				index = y;
		swap(ids[x], ids[index]);
	}
	index = 0;
	while (ids[index] == index) { index++; } //find the first possible unique ID
	c.setID(index); //give the new copy a unique ID

	//Find the book in the database if it already exists
	for(int i = 0; i < Database::getBooks().size(); i++) 
		if (Database::getBooks()[i].getISBN() == b.getISBN()) {
			Database::getBooks()[i].setCount(Database::getBooks()[i].getCount() + 1); //increase copy count
			c.setBook(&Database::getBooks()[i]);  //set the reference book of the copy to the one in the database already
			Database::getCopies().push_back(c);
			cout << endl << "Successfully created a new copy with ID #" << index << " as the book with ISBN: " << b.getISBN() << " was already found in the database." << endl << endl;
			return;
		}

	//If no pre-existing book was found:
	Database::getBooks().push_back(b); //add new book to database
	c.setBook(&Database::getBooks()[Database::getBooks().size() - 1]); //set book pointer to newly added book
	Database::getCopies().push_back(c);
	Database::save(); //save back to text files
}

//Option 3
void Librarian::deleteBook(istream& in) {
	cout << "Enter the ID of the book you wish to delete: ";
	int id;
	in >> id;
	if (Database::getCopyByID(id) >= 0) //Check for valid book
		if (Database::getCopies()[Database::getCopyByID(id)].getBorrower() == "none") {
			//Can only delete if the copy is not lent out
			for (int i = 0; i < Database::getReaders().size(); i++) //look through all users
				for (int z = 0; z < (Database::getReaders()[i].getReserved()).size(); z++) //look through each reserve list of each user
					if (Database::getReaders()[i].getReserved()[z]->getID() == id) //if the copy exists within their reserve list, remove it
						Database::getReaders()[i].getReserved().erase(Database::getReaders()[i].getReserved().begin() + z);
			//Find other copies with the same book
			bool other = false;
			for (Copy c : Database::getCopies())
				if (other = c.getBook() == Database::getCopies()[Database::getCopyByID(id)].getBook() && c.getID() != id)
					break;
			if (!other)//if this is the last copy, delete the book as well
				Database::getBooks().erase(Database::getBooks().begin() + Database::getBookByISBN(Database::getCopies()[Database::getCopyByID(id)].getBook()->getISBN()));
			Database::getCopies().erase(Database::getCopies().begin() + Database::getCopyByID(id)); //delete the whole book
			cout << endl << "Successfully deleted Book with ID #" << id << endl;
			Database::save();
		}
		else
			cout << "Unable to delete book. This copy has already been lent out to a reader." << endl;
	else
		cout << endl << "Book with ID #" << id << " was not found." << endl;
}

//Option 4
void Librarian::searchUsers(istream& in) {
	cout << "Enter the username of the user you wish to print data from: ";
	string user;
	in >> user;
	user = Database::toLower(user);
	for (int i = 0; i < Database::getReaders().size(); i++)
		if (Database::toLower(Database::getReaders()[i].getUsername()) == user) {
			Database::getReaders()[i] << cout;
			if (i <= Database::getPartitioner())
				cout << "Type: Student" << endl;
			else
				cout << "Type: Teacher" << endl;
			return;
		}
	for (Librarian l : Database::getAdmins())
		if (Database::toLower(l.getUsername()) == user) {
			l << cout;
			return;
		}
	cout << endl << "No user with those credentials were found." << endl;
}

//Option 5
void Librarian::addUser(istream& in) {
	int oldPart = Database::getPartitioner();
	int libSize = Database::getAdmins().size();
	cout << endl << endl;
	if (UserAuthentication::signup(in)) {
		cout << "Successfully generated new user." << endl << endl;
		if (Database::getAdmins().size() > libSize) //Print New Admin
			Database::getAdmins()[Database::getAdmins().size() - 1] << cout;
		else if (Database::getPartitioner() > oldPart) //Print New Student
			Database::getReaders()[oldPart + 1] << cout;
		else //Print New Teacher
			Database::getReaders()[Database::getReaders().size() - 1] << cout;
	}
	else
		cout << "Failed to create new user. Username is already in use." << endl;
}

//Option 6
void Librarian::deleteUser(istream& in) {
	cout << "Enter the username of the user you wish to delete: ";
	string user;
	in >> user;
	user = Database::toLower(user);
	if (user != getUsername()) {
		for (int i = 0; i < Database::getReaders().size(); i++) //Student and Teacher Accounts
			if (Database::getReaders()[i].getUsername() == user)
				if (Database::getReaders()[i].getBorrowedBookList().empty()) { //Check if the user has not borrowed any books
					Database::getReaders().erase(Database::getReaders().begin() + i);
					//Delete User from Reserve List
					for (int x = 0; x < Database::getCopies().size(); x++) //look through each copy
						for (int y = 0; y < Database::getCopies()[x].getReservers().size(); y++) //look through the reserver of each copy
							if (Database::toLower(Database::getCopies()[x].getReservers()[y]) == user) { //delete the user and their reserve date from the copy
								Database::getCopies()[x].getReservers().erase(Database::getCopies()[x].getReservers().begin() + y);
								Database::getCopies()[x].getReserveDates().erase(Database::getCopies()[x].getReserveDates().begin() + y);
							}
					cout << "Successfully erased - Username: " << user << endl;
					return;
				}
		for (int i = 0; i < Database::getAdmins().size(); i++) //Admin Accounts
			if (Database::getAdmins()[i].getUsername() == user) {
				Database::getAdmins().erase(Database::getAdmins().begin() + i);
				cout << "Successfully erased - Username: " << user << endl;
				return;
			}
		cout << endl << endl << "Could not find a user with the username: " << user << endl;
	}
	else
		cout << "You cannot delete your own account whilst signed in!" << endl;
}