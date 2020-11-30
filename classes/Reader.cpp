#include "Reader.h"
#include <iostream>
#include "Database.h"
#include "Display.h"

Reader::Reader(): //Reader default is the same as student default
	User(),
	term(30), //by default max borrow period is <=30
	max(5), //by default max 5 books can be borrowed
	borrowed(vector<Copy>()),
	penalties(0),
	reserved(vector<Copy>())
{}

Reader::Reader(string username, string password, int term, int max, vector<Copy> borrowed, vector<Copy> reserved):
	User(username, password),
	term(term),
	max(max),
	borrowed(borrowed),
	penalties(0),
	reserved(reserved)
{}

//Accessor
int Reader::getTerm() { return term; }
int Reader::getMaxCopies() { return max; }
vector<Copy>& Reader::getBorrowedBookList() { return borrowed; }
vector<Copy>& Reader::getReserved() { return reserved; }
int Reader::getPenalties() { return penalties; }

//Mutators
void Reader::setTerm(int term) { this->term = term; }
void Reader::setMaxCopies(int max) { this->max = max; }
void Reader::setBorrowed(vector<Copy> borrowed) { this->borrowed = borrowed; }
void Reader::setPenalties(int penalties) { this->penalties = penalties; }
void Reader::setReserved(vector<Copy> reserved) { this->reserved = reserved; }

//Reads in a single reader from an istream and adds it to the database
istream& Reader::operator>>(istream& in) {
	string line;
	if (!in.eof())
		for (int i = 0; i < 8; i++) {
			getline(in >> ws, line);
			if (line.empty())
				break;
			switch (i) {
			case 0:
				setUsername(line);
				break;
			case 1:
				setPassword(line);
				break;
			case 2:
				term = stoi(line);
				break;
			case 3:
				max = stoi(line);
				break;
			case 4:
				borrowed.clear();
				for (string id : Database::split(line))
					if (stoi(id) > 0)
						borrowed.push_back(Database::getCopies().at(Database::getCopyByID(stoi(id))));
				break;
			case 5:
				penalties = stoi(line);
				break;
			case 6:
				reserved.clear();
				for (string id : Database::split(line))
					if (stoi(id) > 0)
						reserved.push_back(Database::getCopies().at(Database::getCopyByID(stoi(id))));
				break;
			case 7:
				//line delimiter
				break;
			}
		}
	return in;
}

//Write to ostream
ostream& Reader::operator<<(ostream& out) {
	if (&out == &cout) { //Console Display
		out << "Username: " << getUsername() << endl;
		out << "Password: " << getPassword() << endl;
		out << "Borrow Period: " << term << endl;
		out << "Max Number of Books you are able to Borrow: " << max << endl;
		out << "Penalty: " << penalties << endl;
		out << "Currently Borrowed Books: " << endl << endl;
		for (Copy c : borrowed) {
			c << out;
			out << endl;
		}
		out << "Currently Reserved Books: " << endl << endl;
		for (Copy c : reserved) {
			c << out;
			out << endl;
		}
	}
	else { //Write to File
		out << endl << getUsername() << endl;
		out << getPassword() << endl;
		out << term << endl;
		out << max << endl;
		if (!borrowed.empty())
			for (Copy c : borrowed) //puts all books IDs on a line delimited by a space
				out << c.getID() << " ";
		else
			out << -1 << " "; //Indicates no books borrowed
		out << endl << penalties << endl;
		if (!reserved.empty())
			for (Copy c : reserved) //puts all books IDs on a line delimited by a space
				out << c.getID() << " ";
		else
			out << -1 << " "; //Indicates no books borrowed
		out << endl << "----------------";
	}
	return out;
}

bool Reader::operator==(Reader& r) { return getUsername() == r.getUsername() && getPassword() == r.getPassword(); }

//Checks for overdue books and remove overdue reservations <no penalty is issued>
bool Reader::anyOverdue() {
	for (int i = 0; i < Database::getCopies().size(); i++)
		for (int k = 0; k < Database::getCopies()[i].getReservers().size(); k++)
			if (Date::getDays() > Database::getCopies()[i].getReserveDates()[k]) {
				Database::getCopies()[i].getReserveDates().erase(Database::getCopies()[i].getReserveDates().begin() + k);//remove the date
				Database::getCopies()[i].getReservers().erase(Database::getCopies()[i].getReservers().begin() + k);//renove the reservee from the copy vector
				for (int z = 0; z < reserved.size(); z++) //remove from user reserved vector
					if (Database::getCopies()[i].getID() == reserved[z].getID())
						reserved.erase(reserved.begin() + z);
			}
	Database::save();
	for (Copy c : borrowed)
		if (Date::getDays() > c.getExpirationDate()) {
			cout << "You have overdue book(s). You are not allowed to borrow/reserve/renew any more books." << endl;
			return true;
		}
	return false;
}

//Checks if a specific copy is overdue
bool Reader::isOverdue(Copy* c) {
	if (Date::getDays() > c->getExpirationDate()) {
		penalties++; //increase penalty if overdue
		if (penalties % 5 == 0 && penalties > 5) //penalties>5 and if penalties is a multiple of 5 decrease max #
			max--;
		return true;
	}
	return false;
}

//Option 2 - Borrow Books --- Only Issue is Reserve Dates
void Reader::borrowBooks(istream& in) {
	if (!anyOverdue()) //Check for overdue
		if (getMaxCopies() > getBorrowedBookList().size()) { //Check if they haven't checked out more than their maximum
			int id;
			cout << "ID of desired book: "; //Input for desired book ID
			in >> id;
			if (Database::getCopyByID(id) >= 0) { //Check for invalid ID
				Copy* desired = &Database::getCopies().at(Database::getCopyByID(id)); //A pointer is used here to modify the value directly in the database instead of a copy of the value
				
				int res = 0; //total number of reservations
				for (Copy c : Database::getCopies())
					if (c.getBook() == desired->getBook())
						res += c.getReservers().size();
				res = floor(res / 20); //every 20 reservees the borrow period goes down by 1

				if (desired->getBorrower() == "none") { //If nobody has borrowed the book, set the book's information to that of the borrower
					if (desired->getReservers().empty() || desired->getReservers()[0] == getUsername()) { //If no reservations or current reserver
						//Book Modifications
						desired->setBorrower(getUsername());
						desired->setStartDate(Date::getDays()); //set start period to current date
						desired->setExpirationDate(Date::getDays() + (term - res)); //borrow time is based on popularity
						desired->setAvailability(false);
						desired->getBook()->setCount(desired->getBook()->getCount() - 1);

						//User Modifications
						getBorrowedBookList().push_back(*desired); //add to borrowed book list
						cout << endl << "Successfully borrowed Book #" << id << endl << endl << endl;
						if (!desired->getReservers().empty() && desired->getReservers()[0] == getUsername()) {
							desired->getReservers().erase(desired->getReservers().begin()); //Remove from reserve queue
							desired->getReserveDates().erase(desired->getReserveDates().begin());
							for (int z = 0; z < reserved.size(); z++) //remove from user reserved vector
								if (id == reserved[z].getID())
									reserved.erase(reserved.begin() + z);
						}
						Database::getCopies().at(Database::getCopyByID(id)) << cout; //Print recently borrowed book info
						Database::save(); //write back to database files
						return;
					}
				}
				else //If they have a reservation on one book but another copy with a different ID is available, they can borrow it
					for (int i = 0; i < Database::getCopies().size(); i++)
						if (Database::getCopies()[i].getBook() == desired->getBook() && Database::getCopies()[i].getBorrower() == "none")
							if (desired->getReservers()[0] == getUsername()) {
								//Book Modifications
								Database::getCopies()[i].setBorrower(getUsername());
								Database::getCopies()[i].setStartDate(Date::getDays()); //set start period to current date
								Database::getCopies()[i].setExpirationDate(Date::getDays() + (term - res));
								Database::getCopies()[i].setAvailability(false);
								Database::getCopies()[i].getBook()->setCount(Database::getCopies()[i].getBook()->getCount() - 1);

								//User Modifications
								getBorrowedBookList().push_back(Database::getCopies()[i]); //add to borrowed book list
								cout << endl << "As ID #" << id << " was not available, You have successfully borrowed an equivalent copy. ID #" << Database::getCopies()[i].getID() << endl << endl;
								desired->getReservers().erase(desired->getReservers().begin()); //Remove from reserve queue
								desired->getReserveDates().erase(desired->getReserveDates().begin());
								for (int z = 0; z < reserved.size(); z++) //remove from user reserved vector
									if (id == reserved[z].getID())
										reserved.erase(reserved.begin() + z);
								Database::getCopies()[i] << cout; //Print recently borrowed book info
								Database::save(); //write back to database files
								return;
							}
				cout << "Unfortunately, this book has already been borrowed and no other copies are available. Please choose a different book." << endl;
			}
			else
				cout << "The desired book, given ID: #" << id << " was not found." << endl;
		}
		else
			cout << "You have reached your limit on books! Please return a book. " << endl;
}

//Option 3 - Return Books
void Reader::returnBooks(istream& in) {
	int id;
	cout << "ID of book to return: "; //Input for desired book ID
	in >> id;
	if (Database::getCopyByID(id) >= 0) { //Check for invalid ID
		Copy* desired = &Database::getCopies()[Database::getCopyByID(id)]; //A pointer is used here to modify the value directly in the database instead of a copy of the value
		for (int i = 0; i < getBorrowedBookList().size(); i++)
			if (getBorrowedBookList().at(i).getID() == id) { //Check if the user has borrowed a book with the given ID
				anyOverdue(); //remove overdue reservations
				isOverdue(desired); //Check for penalty and issue penalty if a book is overdue
				//Reset Book attributes
				desired->setBorrower("none");
				desired->setStartDate(0);
				desired->setExpirationDate(0);
				desired->setAvailability(true);
				desired->getBook()->setCount(desired->getBook()->getCount() + 1);
				getBorrowedBookList().erase(getBorrowedBookList().begin() + i); //remove from borrowed list
				Database::save(); //write back to database files
				cout << endl << "Successfully returned Book #" << id << endl << endl << endl;
				Database::getCopies().at(Database::getCopyByID(id)) << cout; //Print recently returned book info
				return;
			}
		cout << "Error. You have not borrowed a book with the ID #" << id << endl;
	}
	else
		cout << "ID #"<< id << " does not exist within our database." << endl;
}

//Option 4 - Reserve Books
void Reader::reserveBooks(istream& in) {
	//Make Reservations
	if (!anyOverdue()) {
		cout << "Enter the ID of the book you would like to reserve: ";
		int id;
		in >> id;
		if (Database::getCopyByID(id) >= 0) { //Check if the copy exists in the database
			Copy* desired = &Database::getCopies()[Database::getCopyByID(id)];
			for (string user : desired->getReservers())
				if (user == getUsername()) {
					cout << "You already have an existing reservation. " << endl;
					return;
				}
			if (desired->getBorrower() == getUsername()) {
				cout << "You cannot reserve a book that you have already borrowed. However, you may renew this book." << endl;
				return;
			}
			desired->getReservers().push_back(getUsername()); //push to reservee vector
			if (desired->getReserveDates().empty()) //If this is the first reserver, their reserve date is 5 days after the current borrower's expiration date
				if(desired->getBorrower()!="none")
					desired->getReserveDates().push_back(desired->getExpirationDate() + 5);
				else //If there is no current borrower the reserve date is 5 days from now
					desired->getReserveDates().push_back(Date::getDays() + 5);
			else //If this is not the first reserver, the date is 5 days after the previous reservee's reservation date
				desired->getReserveDates().push_back(desired->getReserveDates()[desired->getReserveDates().size() - 1] + 5);
			cout << "Successfully reserved the following book:" << endl << endl;
			reserved.push_back(*desired);
			reserved[reserved.size()-1] << cout; //check if it was correctly saved in user vector
			cout << "Reserve Date is: " << desired->getReserveDates()[desired->getReserveDates().size() - 1] << endl;
		}
		else
			cout << "The desired book with the ID #" << id << " was not found in the database." << endl;
	}
	Database::save();
}

//Option 5 - Cancel Reservations
void Reader::cancelReserve(istream& in) {
	cout << "Enter the ID of the book that has the reservation you wish to cancel: ";
	int id;
	in >> id;
	if (Database::getCopyByID(id) >= 0) {
		for (int i = 0; i < Database::getCopies()[Database::getCopyByID(id)].getReservers().size(); i++)
			if (Database::getCopies()[Database::getCopyByID(id)].getReservers()[i] == getUsername()) { //find the username in the reserve vector
				Copy* desired = &Database::getCopies()[Database::getCopyByID(id)];
				desired->getReservers().erase(desired->getReservers().begin() + i);
				desired->getReserveDates().erase(desired->getReserveDates().begin() + i);
				for (int z = 0; z < reserved.size(); z++) //remove from user reserved vector
					if (id == reserved[z].getID())
						reserved.erase(reserved.begin() + z);
				Database::save();
				cout << "Successfully Cancelled Reservation on: " << endl;
				*desired << cout;
				return;
			}
		cout << "You do not currently have a reservation on ID #" << id << endl;
	}
	else
		cout << "The desired book with the ID #" << id << " was not found in the database." << endl;
}

//Option 6 - Renew Books
void Reader::renewBooks(istream& in) {
	if (!anyOverdue()) {
		cout << "Enter the ID of the book you wish to renew: ";
		int id;
		in >> id;
		if (Database::getCopyByID(id) >= 0) //If the ID is valid, the reservation list is empty and the current reader is the borrower
			if (Database::getCopies()[Database::getCopyByID(id)].getReservers().empty() && Database::getCopies()[Database::getCopyByID(id)].getBorrower() == getUsername()) {
				Copy* desired = &Database::getCopies()[Database::getCopyByID(id)];
				desired->setExpirationDate(desired->getExpirationDate() + term);
				cout << "Successfully Renewed ID #" << id << endl;
				*desired << cout;
				return;
			}
			else
				cout << "Renewal Failed. Either reservations are present on this book or you are not the current borrower" << endl;
		cout << "The desired book with the ID #" << id << " was not found in the database." << endl;
	}
	Database::save();
}
