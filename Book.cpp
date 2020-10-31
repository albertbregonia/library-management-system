// Xiangfeng Lin for the cpp file 10/16

#pragma once
#include <iostream>
#include "Book.h"

//Constructors
Book::Book() {}
Book::Book(string ISBN, string title, string author, string category, int id, string reader, long start, long end) :
	ISBN(ISBN),
	author(author),
	category(category),
	id(id),
	reader(reader),
	start(start),
	end(end)
{}

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
	}
	return out;
}

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