#pragma once
#include <iostream>
#include "Book.h"
#include "Database.h"

//Constructors
Book::Book():
	ISBN("0"),
	title("title"),
	author("author"),
	category("category"),	
{}
Book::Book(string ISBN, string title, string author, string category) :
	ISBN(ISBN),
	title(title),
	author(author),
	category(category),
{}

//Accessors
string Book::getISBN() {return ISBN;}
string Book::getTitle() {return title;}
string Book::getAuthor() {return author;}
string Book::getCategory() {return category;}


//Mutators
void Book::setISBN(string ISBN) {this->ISBN = ISBN;}
void Book::setTitle(string title) {this->title = title;}
void Book::setAuthor(string author) {this->author = author;}
void Book::setCategory(string category) {this->category = category;}


//Overloaded Operators
ostream& Book::operator<<(ostream& out) const {
	if (&out == &cout) { //Console Display
		out << "ISBN: " << ISBN << endl;
		out << "Title: " << title << endl;
		out << "Author: " << author << endl;
		out << "Category: " << category << endl;
		out << "ID: " << id << endl;
		out << "Current Borrower: " << reader << endl;
		out << "Start Date: " << start << endl;
		out << "Expiration Date: " << end << endl;
	}
	else { //Write to File
		out << ISBN << endl;
		out << title << endl;
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

//Reads in a single book from a stream and adds it to the book database
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
					Database::getBooks().push_back(*this);
			}
		}
	return in;
}