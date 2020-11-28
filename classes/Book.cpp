#pragma once
#include <iostream>
#include "Book.h"
#include "Database.h"

//Constructors
Book::Book():
	ISBN("0"),
	title("title"),
	author("author"),
	category("category")	
{}
Book::Book(string ISBN, string title, string author, string category, string index, int count, int favor) :
	ISBN(ISBN),
	title(title),
	author(author),
	category(category),
	index(index),
	count(count),
	favor(favor)
{}

//Accessors
string Book::getISBN() {return ISBN;}
string Book::getTitle() {return title;}
string Book::getAuthor() {return author;}
string Book::getCategory() {return category;}
string Book::getIndex() { return index; }
int Book::getCount() { return count; }
int Book::getFavor() { return favor; }

//Mutators
void Book::setISBN(string ISBN) {this->ISBN = ISBN;}
void Book::setTitle(string title) {this->title = title;}
void Book::setAuthor(string author) {this->author = author;}
void Book::setCategory(string category) {this->category = category;}
void Book::setIndex(string i) { this->index = i; }
void Book::setCount(int i) { this->count = i; }
void Book::setFavor(int i) { this->favor = i; }

//Overloaded Operators
ostream& Book::operator<<(ostream& out) const {
	if (&out == &cout) { //Console Display
		out << "ISBN: " << ISBN << endl;
		out << "Title: " << title << endl;
		out << "Author: " << author << endl;
		out << "Category: " << category << endl;
	}
	else { //Write to File
		out << ISBN << endl;
		out << title << endl;
		out << author << endl;
		out << category << endl;
		out << "----------------" << endl;
	}
	return out;
}

//Reads in a single book from a stream and adds it to the book database
istream& Book::operator>>(istream& in) {
	string line;
	if(!in.eof())
		for (int i = 0; i < 5; i++) {
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
					//line delimiter
			}
		}
	return in;
}