// Xiangfeng Lin for the cpp file 10/16

#pragma once
#include <iostream>
#include "Book.h"

//Constructors
Book::Book() {}
Book::Book(long ISBN, string title, string author, string category, int id, string reader, long start, long end) :
	ISBN(ISBN),
	author(author),
	category(category),
	id(id),
	reader(reader),
	start(start),
	end(end)
{}

void Book::print() {  //show the information of the book
	cout << "\tISBN:" << ISBN << endl;
	cout << "\ttitle:" << title << endl;
	cout << "\tauthor:" << author << endl;
	cout << "\tcategory:" << category << endl;
	cout << "\tID:"<< id << endl;
	cout << "\tReader:" << reader << endl;
	cout << "\tStart date:" << start << endl;
	cout << "\tExpiration date:" << end << endl;
}

//Accessors
long Book::getISBN() {return ISBN;}
string Book::getTitle() {return title;}
string Book::getAuthor() {return author;}
string Book::getCategory() {return category;}
int Book::getID() {return id;}
string Book::getBorrower() {return reader;}
long Book::getStartDate() {return start;}
long Book::getExpirationDate() {return end;}

//Mutators
void Book::setISBN(long ISBN) {this->ISBN = ISBN;}
void Book::setTitle(string title) {this->title = title;}
void Book::setAuthor(string author) {this->author = author;}
void Book::setCategory(string category) {this->category = category;}
void Book::setID(int id) {this->id = id;}
void Book::setBorrower(string reader) {this->reader = reader;}
void Book::setStartDate(long start) {this->start = start;}
void Book::setExpirationDate(long end) {this->end = end;}
