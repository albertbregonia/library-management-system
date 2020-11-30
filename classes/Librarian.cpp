#include "Librarian.h"
#include "Database.h"
#include <iostream>

//Constructor
Librarian::Librarian() : User("admin", "admin") {}

Librarian::Librarian(string username, string password) : User(username, password) {}

void Librarian::deleteBook(istream& in) {
	cout << "Enter the ID of the book you wish to delete: ";
	int id;
	in >> id;
	if (Database::getCopyByID(id) >= 0) {//-1 if no book
		Database::getCopies().erase(Database::getCopies().begin() + Database::getCopyByID(id));
		cout << "Successfully deleted Book with ID #" << id << endl;
	}
}

void Librarian::deleteUser(istream& in) {
	cout << "Enter the username of the user you wish to delete: ";
	string user;
	in >> user;
	user = Database::toLower(user);
	for (int i = 0; i < Database::getReaders().size(); i++) //Student and Teacher Accounts
		if (Database::toLower(Database::getReaders()[i].getUsername()) == user)
			if (Database::getReaders()[i].getBorrowedBookList().empty()) {
				Database::getReaders().erase(Database::getReaders().begin() + i);
				//Delete User from Reserve List
				for (int x = 0; x < Database::getCopies().size(); x++)
					for (int y = 0; y < Database::getCopies()[x].getReservers().size(); y++)
						if (Database::toLower(Database::getCopies()[x].getReservers()[y]) == user)
							Database::getCopies()[x].getReservers().erase(Database::getCopies()[x].getReservers().begin() + y);
				cout << "Successfully erased - Username: " << user << endl;
				return;
			}
	for(int i = 0; i < Database::getAdmins().size(); i++) //Admin Accounts
		if(Database::toLower(Database::getAdmins()[i].getUsername()) == user) {
			Database::getAdmins().erase(Database::getAdmins().begin() + i);
			cout << "Successfully erased - Username: " << user << endl;
			return;
		}
}

void Librarian::searchUsers(istream& in) {
	cout << "Enter the username of the user you wish to print data from: ";
	string user;
	in >> user;
	user = Database::toLower(user);
	for (Reader r : Database::getReaders())
		if (Database::toLower(r.getUsername()) == user) {
			r << cout;
			return;
		}
	for (Librarian l : Database::getAdmins())
		if (Database::toLower(l.getUsername()) == user) {
			l << cout;
			return;
		}
}