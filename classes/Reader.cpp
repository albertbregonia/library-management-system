#include "Reader.h"
#include <iostream>
#include "Database.h"
#include "Display.h"

Reader::Reader(): //Reader default is the same as student default
	User(),
	term(30), //by default max borrow period is <=30
	max(5), //by default max 5 books can be borrowed
	borrowed(vector<Copy*>()),
	penalties(0),
	reserved(vector<Copy*>())
{}

Reader::Reader(string username, string password, int term, int max, vector<Copy*> borrowed, vector<Copy*> reserved):
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
vector<Copy*>& Reader::getBorrowedBookList() { return borrowed; }
vector<Copy*>& Reader::getReserved() { return reserved; }
int Reader::getPenalties() { return penalties; }

//Mutators
void Reader::setTerm(int term) { this->term = term; }
void Reader::setMaxCopies(int max) { this->max = max; }
void Reader::setBorrowed(vector<Copy*> borrowed) { this->borrowed = borrowed; }
void Reader::setPenalties(int penalties) { this->penalties = penalties; }
void Reader::setReserved(vector<Copy*> reserved) { this->reserved = reserved; }

//Write to ostream
ostream& operator<<(ostream& out, Reader& r) {
	if (&out == &cout) { //Console Display
		out << "Username: " << r.getUsername() << endl;
		out << "Password: " << r.getPassword() << endl;
		out << "Borrow Period: " << r.term << endl;
		out << "Max Number of Books you are able to Borrow: " << r.max << endl;
		out << "Penalty: " << r.penalties << endl;
		out << "Currently Borrowed Books: " << endl << endl;
		for (Copy* c : r.borrowed) {
			out << *c;
			out << endl;
		}
		out << "Currently Reserved Books: " << endl << endl;
		for (Copy* c : r.reserved) {
			out << *c;
			out << endl;
		}
	}
	else { //Write to File
		out << endl << r.getUsername() << endl;
		out << r.getPassword() << endl;
		out << r.term << endl;
		out << r.max << endl;
		if (!r.borrowed.empty())
			for (Copy* c : r.borrowed) //puts all books IDs on a line delimited by a space
				out << c->getID() << " ";
		else
			out << -1 << " "; //Indicates no books borrowed
		out << endl << r.penalties << endl;
		if (!r.reserved.empty())
			for (Copy* c : r.reserved) //puts all books IDs on a line delimited by a space
				out << c->getID() << " ";
		else
			out << -1 << " "; //Indicates no books borrowed
		out << endl << "----------------";
	}
	return out;
}

//Reads in a single reader from an istream and adds it to the database
istream& operator>>(istream& in, Reader& r) {
	string line;
	if (!in.eof())
		for (int i = 0; i < 8; i++) {
			getline(in >> ws, line);
			if (line.empty())
				break;
			switch (i) {
			case 0:
				r.setUsername(line);
				break;
			case 1:
				r.setPassword(line);
				break;
			case 2:
				r.term = stoi(line);
				break;
			case 3:
				r.max = stoi(line);
				break;
			case 4:
				r.borrowed.clear();
				for (string id : Database::split(line))
					if (stoi(id) > 0)
						r.borrowed.push_back(&Database::getCopies().at(Database::getCopyByID(stoi(id))));
				break;
			case 5:
				r.penalties = stoi(line);
				break;
			case 6:
				r.reserved.clear();
				for (string id : Database::split(line))
					if (stoi(id) > 0)
						r.reserved.push_back(&Database::getCopies().at(Database::getCopyByID(stoi(id))));
				break;
			case 7:
				//line delimiter
				break;
			}
		}
	return in;
}

//Checks for overdue books and remove overdue reservations <no penalty is issued>
bool Reader::anyOverdue() {
	for (int i = 0; i < Database::getCopies().size(); i++)
		for (int k = 0; k < Database::getCopies()[i].getReservers().size(); k++)
			if (Date::getDays() > Database::getCopies()[i].getReserveDates()[k]) {
				Database::getCopies()[i].getReserveDates().erase(Database::getCopies()[i].getReserveDates().begin() + k);//remove the date
				Database::getCopies()[i].getReservers().erase(Database::getCopies()[i].getReservers().begin() + k);//renove the reservee from the copy vector
				for (int z = 0; z < reserved.size(); z++) //remove from user reserved vector
					if (Database::getCopies()[i].getID() == reserved[z]->getID())
						reserved.erase(reserved.begin() + z);
			}
	Database::save();
	for (Copy* c : borrowed)
		if (Date::getDays() > c->getExpirationDate()) {
			cout << "You have overdue book(s). You are not allowed to borrow/reserve/renew any more books." << endl;
			return true;
		}
	return false;
}

//Checks if a specific copy is overdue - issues a penalty
bool Reader::isOverdue(Copy* c) {
	if (Date::getDays() > c->getExpirationDate()) {
		penalties++; //increase penalty if overdue
		if (penalties == 6 || (penalties % 5 == 0 && penalties>5)) //penalties>5 and if penalties is a multiple of 5 decrease max #
			max--;
		return true;
	}
	return false;
}

//Option 2 - Borrow Books
void Reader::borrowBooks(istream& in) {
	if (!anyOverdue()) //Check for overdue
		if (getMaxCopies() > getBorrowedBookList().size()) { //Check if they haven't checked out more than their maximum
			cout << "ID of desired book: "; //Input for desired book ID
			int id = Database::inputHandler(in);
			if (Database::getCopyByID(id) >= 0) { //Check for invalid ID
				Copy* desired = &Database::getCopies().at(Database::getCopyByID(id)); //A pointer is used here to modify the value directly in the database instead of a copy of the value
				int res = Database::getBookPopularity(desired->getBook()->getISBN()); //total number of reservations
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
						getBorrowedBookList().push_back(desired); //add to borrowed book list
						cout << endl << "Successfully borrowed Book #" << id << endl << endl << endl;
						if (!desired->getReservers().empty() && desired->getReservers()[0] == getUsername())
							Database::deleteReserver(*this, *desired, 0); //delete
						cout << *desired; //Print recently borrowed book info
						Database::save(); //write back to database files
						return;
					}
				} //If they have a reservation on one book but another copy with a different ID is available, they can borrow it
				else
					for (Copy* c:Database::getAllCopiesByISBN(desired->getBook()->getISBN()))
						if (c->getBorrower() == "none" && c->getReservers().empty()){ //Book has no reservors and no borrower
							//Book Modifications
							c->setBorrower(getUsername());
							c->setStartDate(Date::getDays()); //set start period to current date
							c->setExpirationDate(Date::getDays() + (term - res));
							c->setAvailability(false);
							c->getBook()->setCount(c->getBook()->getCount() - 1);

							//User Modifications
							getBorrowedBookList().push_back(c); //add to borrowed book list
							cout << endl << "As ID #" << id << " was not available, You have successfully borrowed an equivalent copy. ID #" << c << endl << endl;
							Database::deleteReserver(*this, *desired, 0); //delete
							cout << c; //Print recently borrowed book info
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
	cout << "ID of book to return: "; //Input for desired book ID
	int id = Database::inputHandler(in);
	if (Database::getCopyByID(id) >= 0) { //Check for invalid ID
		Copy* desired = &Database::getCopies()[Database::getCopyByID(id)]; //A pointer is used here to modify the value directly in the database instead of a copy of the value
		int pos = Database::getCopyInBorrowedList(*this, id);
		if (pos >= 0) {
			anyOverdue(); //remove overdue reservations
			isOverdue(desired); //Check for penalty and issue penalty if a book is overdue
			//Reset Book attributes
			desired->setBorrower("none");
			desired->setStartDate(0);
			desired->setExpirationDate(0);
			desired->setAvailability(true);
			desired->getBook()->setCount(desired->getBook()->getCount() + 1);
			getBorrowedBookList().erase(getBorrowedBookList().begin() + pos); //remove from borrowed list
			cout << endl << "Successfully returned Book #" << id << endl << endl << endl;
			cout << *desired; //Print recently returned book info
			Database::save(); //write back to database files
		}
		else
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
		int id = Database::inputHandler(in);
		if (Database::getCopyByID(id) >= 0) { //Check if the copy exists in the database
			Copy* desired = &Database::getCopies()[Database::getCopyByID(id)];
			if (Database::getCopyInBorrowedList(*this, id) < 0) //reader has not borrowed this book
				if (Database::getUserInReservers(*desired, getUsername()) < 0) { //reader has not reserved this book
					desired->getReservers().push_back(getUsername()); //push to reservee vector
					if (desired->getReserveDates().empty()) //If this is the first reserver, their reserve date is 5 days after the current borrower's expiration date
						if (desired->getBorrower() != "none")
							desired->getReserveDates().push_back(desired->getExpirationDate() + 5);
						else //If there is no current borrower the reserve date is 5 days from now
							desired->getReserveDates().push_back(Date::getDays() + 5);
					else //If this is not the first reserver, the date is 5 days after the previous reservee's reservation date
						desired->getReserveDates().push_back(desired->getReserveDates()[desired->getReserveDates().size() - 1] + 5);
					cout << "Successfully reserved the following book:" << endl << endl;
					reserved.push_back(desired);
					cout << *reserved[reserved.size() - 1]; //check if it was correctly saved in user vector
					cout << "Reserve Date is: " << desired->getReserveDates()[desired->getReserveDates().size() - 1] << endl;
				}
				else
					cout << "You already have an existing reservation. " << endl;
			else
				cout << "You cannot reserve a book that you have already borrowed. However, you may renew this book." << endl;
		}
		else
			cout << "The desired book with the ID #" << id << " was not found in the database." << endl;
	}
	Database::save();
}

//Option 5 - Cancel Reservations
void Reader::cancelReserve(istream& in) {
	cout << "Enter the ID of the book that has the reservation you wish to cancel: ";
	int id = Database::inputHandler(in);
	if (Database::getCopyByID(id) >= 0) {
		Copy* desired = &Database::getCopies()[Database::getCopyByID(id)];
		int pos = Database::getUserInReservers(*desired, getUsername());
		if (pos>=0) {
			Database::deleteReserver(*this, *desired, pos);
			Database::save();
			cout << "Successfully Cancelled Reservation on: " << endl;
			cout << *desired;
		}
		else
			cout << "You do not currently have a reservation on ID #" << id << endl;
	}
	else
		cout << "The desired book with the ID #" << id << " was not found in the database." << endl;
}

//Option 6 - Renew Books
void Reader::renewBooks(istream& in) {
	if (!anyOverdue()) {
		cout << "Enter the ID of the book you wish to renew: ";
		int id = Database::inputHandler(in);
		int pos = Database::getCopyByID(id);
		if (pos >= 0) //If the ID is valid, the reservation list is empty and the current reader is the borrower
			if (Database::getCopies()[pos].getReservers().empty() && Database::getCopies()[pos].getBorrower() == getUsername()) {
				Copy* desired = &Database::getCopies()[pos];
				desired->setExpirationDate(desired->getExpirationDate() + term);
				cout << "Successfully Renewed ID #" << id << endl;
				cout << *desired;
				return;
			}
			else
				cout << "Renewal Failed. Either reservations are present on this book or you are not the current borrower" << endl;
		else
			cout << "The desired book with the ID #" << id << " was not found in the database." << endl;
	}
	Database::save();
}

//Option 9 - Recommend Books
void Reader::recommendBooks() {
	vector<Database::totalBookInfo> list;
	for (int z = 0; z < Database::getBooks().size(); z++) //while the list is <10 and if the borrowed books is not empty and the category matches OR if the list is empty
		if (((!borrowed.empty() && Database::getBooks()[z].getCategory() == borrowed[borrowed.size() - 1]->getBook()->getCategory()) || borrowed.empty()) && list.size() < 10) { //last book's category
			Database::totalBookInfo temp; //Save Book, IDs and Reserve Count for each copy
			temp.book = &Database::getBooks()[z];
			temp.ids = "***IDs: ";
			for (Copy* c : Database::getAllCopiesByTitle(Database::getBooks()[z].getTitle()))//Find all IDs of that Book
				temp.ids += to_string(c->getID()) + " "; //update totalBookInfo to sort by popularity
			temp.numReserves = Database::getBookPopularity(Database::getBooks()[z].getISBN());
			list.push_back(temp); //Add to list of books to sort based on popularity
		}
	Database::sort(list); //selection sort based on number of reserves
	for (Database::totalBookInfo i : list) //Print books
		cout << *i.book << i.ids << endl << endl;
}