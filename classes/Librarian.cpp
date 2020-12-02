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
	in >> b;
	Copy c; //create a New Copy of the book
	int i = 0;
	while (Database::getAllIDs()[i] == i) i++;
	c.setID(i); //find and set the first possible unique ID

	//Find the book in the database if it already exists
	if ((i = Database::getBookByISBN(b.getISBN())) >= 0) {
		Database::getBooks()[i].setCount(Database::getBooks()[i].getCount() + 1); //increase copy count
		c.setBook(&Database::getBooks()[i]);  //set the reference book of the copy to the one in the database already
		Database::getCopies().push_back(c);
		cout << endl << endl << "Successfully created a new copy with ID #" << i << " as the book with ISBN: " << b.getISBN() << " was already found in the database." << endl << endl;
	}
	else { //If no pre-existing book was found:
		Database::getBooks().push_back(b); //add new book to database
		c.setBook(&Database::getBooks()[Database::getBooks().size() - 1]); //set book pointer to newly added book
		Database::getCopies().push_back(c);
	}
	Database::save(); //save back to text files
}

//Option 3
void Librarian::deleteBook(istream& in) {
	cout << "Enter the ID of the book you wish to delete: ";
	int id;
	in >> id;
	int copy;
	if ((copy = Database::getCopyByID(id)) >= 0) { //Check for valid book
		if (Database::getCopies()[copy].getBorrower() == "none") { //Can only delete if the copy is not lent out
			int pos;
			Copy* desired = &Database::getCopies()[copy];
			for (int i = 0; i < Database::getReaders().size(); i++) //look through all users and delete
				if ((pos = Database::getCopyInReserveList(Database::getReaders()[i], id)) >= 0)
					Database::deleteReserver(Database::getReaders()[i], *desired, pos);

			if (!Database::getAllCopiesByISBN(desired->getBook()->getISBN()).size()==1)//if this is the last copy, delete the book as well
				Database::getBooks().erase(Database::getBooks().begin() + Database::getBookByISBN(desired->getBook()->getISBN()));
			Database::getCopies().erase(Database::getCopies().begin() + copy); //delete the copy
			cout << endl << "Successfully deleted Book with ID #" << id << endl;
			Database::save();
		}
		else
			cout << "Unable to delete book. This copy has already been lent out to a reader." << endl;
	}	
	else
		cout << endl << "Book with ID #" << id << " was not found." << endl;
}

//Option 4
void Librarian::searchUsers(istream& in) {
	cout << "Enter the username of the user you wish to print data from: ";
	string user;
	in >> user;
	int i;
	if ((i=Database::getReaderByUsername(user))>=0) {
		cout << Database::getReaders()[i];
		if (i <= Database::getPartitioner())
			cout << "Type: Student" << endl;
		else
			cout << "Type: Teacher" << endl;
	}
	else if ((i = Database::getAdminByUsername(user)) >= 0)
		cout << Database::getAdmins()[i];
	else
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
			cout << Database::getAdmins()[Database::getAdmins().size() - 1];
		else if (Database::getPartitioner() > oldPart) //Print New Student
			cout << Database::getReaders()[oldPart + 1];
		else //Print New Teacher
			cout << Database::getReaders()[Database::getReaders().size() - 1];
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
	int i;
	if (user != getUsername())
		if ((i=Database::getReaderByUsername(user))>=0)
			if (Database::getReaders()[i].getBorrowedBookList().empty()) { //Check if the user has not borrowed any books
				Database::getReaders().erase(Database::getReaders().begin() + i); //Delete User
				//Delete User from Reserve Lists
				int pos;
				for (int x = 0; x < Database::getCopies().size(); x++) //look through each copy and delete the user
					if ((pos = Database::getUserInReservers(Database::getCopies()[x], user)) >= 0)
						Database::deleteReserver(Database::getReaders()[i], Database::getCopies()[x], pos);
				cout << "Successfully erased - Username: " << user << endl;
			}
			else
				cout << "Unfortunately, this user has borrowed books and cannot be deleted at the moment." << endl;
		else if ((i = Database::getAdminByUsername(user)) >= 0) {
			Database::getAdmins().erase(Database::getAdmins().begin() + i);
			cout << "Successfully erased - Username: " << user << endl;
		}
		else
			cout << endl << endl << "Could not find a user with the username: " << user << endl;
	else
		cout << "You cannot delete your own account whilst signed in!" << endl;
}