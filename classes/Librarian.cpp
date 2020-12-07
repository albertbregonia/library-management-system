#include "Librarian.h"
#include "Database.h"
#include "UserAuth.h"
#include "Display.h"
#include <iostream>

//Constructor
Librarian::Librarian() : User("admin", "admin") {}

Librarian::Librarian(string username, string password) : User(username, password) {}

//Option 2
void Librarian::addBook(istream& in) {
	Book b;
	bool error;
	do{ //Do-while to keep taking in an input until no errors occur
		cout << "Please enter in the Book Information." << endl;
		cout << "Please enter in the order of [ISBN - Title - Author - Catgeory - Index -  1 - 0 - End]:" << endl;
		cout << "'1' and '0' are the default 'Count' and 'Favor' attributes. \nIf this book already exists in the database it will adjusted accordingly." << endl;
		cout << "If this is a new book that has not been in the database, these are the default parameters." << endl << endl;
		cout << "Book Information:" << endl;
		try { 
			in >> b;
			error = false;
		}
		catch (...) {
			cerr << endl << endl << endl << "Invalid Input. Please try again" << endl << endl << endl;
			Display::border();
			error = true;
		}
	} while (error);
	Copy c;
	int i = 0;
	while (i < Database::getAllIDs().size() && Database::getAllIDs()[i] == i) i++;
	c.setID(i); //find and set the first possible unique ID

	//Find the book in the database if it already exists
	if ((i = Database::getBookByISBN(b.getISBN())) >= 0) {
		Database::getBooks()[i].setCount(Database::getBooks()[i].getCount() + 1); //increase copy count
		c.setBook(&Database::getBooks()[i]);  //set the reference book of the copy to the one in the database already
		Database::getCopies().push_back(c);
		cout << endl << endl << "Successfully created a new copy with ID #" << c.getID() << " as the book with ISBN: " << b.getISBN() << " was already found in the database." << endl << endl;
	}
	else { //If no pre-existing book was found:

		//As a vector resizes itself Sections A and B were implemented to retain pointer values - Albert Bregonia

		//Section A
		vector<string> former; 
		for (Copy c : Database::getCopies())
			former.push_back(c.getBook()->getISBN());
		//End of Section A

		Database::getBooks().push_back(b); //add new book to database
		c.setBook(&Database::getBooks()[Database::getBooks().size() - 1]); //set book pointer to newly added book
		Database::getCopies().push_back(c);

		//Section B
		for (int k = 0; k < former.size(); k++)
			Database::getCopies()[k].setBook(&Database::getBooks()[Database::getBookByISBN(former[k])]);
		//End of Section B
		cout << endl << endl << "Successfully created a new copy with ID #" << c.getID() << " and a new book with ISBN: " << b.getISBN() << " as it was not found in the database." << endl << endl;
	}
	Database::save(); //save back to text files
}

//Option 3
void Librarian::deleteBook(istream& in) {
	cout << "Enter the ID of the book you wish to delete: ";
	int id = Database::inputHandler(in);
	int copy;
	if ((copy = Database::getCopyByID(id)) >= 0) //Check for valid book
		if (Database::getCopies()[copy].getBorrower() == "none") { //Can only delete if the copy is not lent out
			int pos;
			Copy* desired = &Database::getCopies()[copy];
			for (int i = 0; i < Database::getReaders().size(); i++) //look through all users and delete
				if ((pos = Database::getCopyInReserveList(Database::getReaders()[i], id)) >= 0)
					Database::deleteReserver(Database::getReaders()[i], *desired, pos);

			if (Database::getAllCopiesByISBN(desired->getBook()->getISBN()).size()==1)//if this is the last copy, delete the book as well
				Database::getBooks().erase(Database::getBooks().begin() + Database::getBookByISBN(desired->getBook()->getISBN()));

			//As a vector resizes itself Sections A and B were implemented to retain pointer values - Albert Bregonia

			//Section A
			vector<Book> former;
			for (Copy c : Database::getCopies())
				former.push_back(*c.getBook());
			//End of Section A
			Database::getCopies().erase(Database::getCopies().begin() + copy); //delete the copy

			//Section B
			for (int k = 0; k < former.size()-1; k++)
				Database::getCopies()[k].setBook(&Database::getBooks()[Database::getBookByISBN(former[k].getISBN())]);
			//End of Section B
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
		Database::save();
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
				Database::save();
			}
			else
				cout << "Unfortunately, this user has borrowed books and cannot be deleted at the moment." << endl;
		else if ((i = Database::getAdminByUsername(user)) >= 0) {
			Database::getAdmins().erase(Database::getAdmins().begin() + i);
			cout << "Successfully erased - Username: " << user << endl;
			Database::save();
		}
		else
			cout << endl << endl << "Could not find a user with the username: " << user << endl;
	else
		cout << "You cannot delete your own account whilst signed in!" << endl;
}