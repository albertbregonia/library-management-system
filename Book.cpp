// Xiangfeng Lin for the cpp file 10/16

#pragma once
#include <iostream>
#include "Book.h"
#include "Database.h"

//Constructors
Book::Book():
	ISBN("0"),
	author("author"),
	category("category"),
	id(-10),
	reader("none"),
	start(0),
	end(0) 
{}
Book::Book(string ISBN, string title, string author, string category, int id, string reader, long start, long end) :
	ISBN(ISBN),
	author(author),
	category(category),
	id(id),
	reader(reader),
	start(start),
	end(end)
{}

//Accessors
string Book::getISBN() {return ISBN;}
string Book::getTitle() {return title;}
string Book::getAuthor() {return author;}
string Book::getCategory() {return category;}
int Book::getID() {return id;}
string Book::getBorrower() {return reader;}
long Book::getStartDate() {return start;}
long Book::getExpirationDate() {return end;}

//Mutators
void Book::setISBN(string ISBN) {this->ISBN = ISBN;}
void Book::setTitle(string title) {this->title = title;}
void Book::setAuthor(string author) {this->author = author;}
void Book::setCategory(string category) {this->category = category;}
void Book::setID(int id) {this->id = id;}
void Book::setBorrower(string reader) {this->reader = reader;}
void Book::setStartDate(long start) {this->start = start;}
void Book::setExpirationDate(long end) {this->end = end;}

//Overloaded Operators
ostream& Book::operator<<(ostream& out) const {  //show the information of the book
	if (&out == &cout) { //Console Display
		out << "ISBN: " << ISBN << endl;
		out << "Author: " << author << endl;
		out << "Category: " << category << endl;
		out << "ID: " << id << endl;
		out << "Current Borrower: " << reader << endl;
		out << "Start Date: " << start << endl;
		out << "Expiration Date: " << end << endl;
	}
	else { //Write to File
		out << ISBN << endl;
		out << author << endl;
		out << category << endl;
		out << id << endl;
		out << reader << endl;
		out << start << endl;
		out << end << endl;
		out << "----------------" << endl;
	}
	return out;
}

istream& Book::operator>>(istream& in) {
	string line;
	if(!in.eof())
		for (int i = 0; i < 9; i++) {
			getline(in, line);
			if (line.empty())
				break;
			switch (i) {
				case 0:
					ISBN = line;
					break;
				case 1:
					title = line;
					break;
				case 2:
					author = line;
					break;
				case 3:
					category = line;
					break;
				case 4:
					id = stoi(line);
					break;
				case 5:
					reader = line;
					break;
				case 6:
					start = stol(line);
					break;
				case 7:
					end = stol(line);
					break;
				case 8: //line delimiter
					Database::getBooks().push_back(Book(ISBN, title, author, category, id, reader, start, end));
			}
		}
	return in;
}