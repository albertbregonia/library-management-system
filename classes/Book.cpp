#pragma once
#include <iostream>
#include "Book.h"

//Constructors
Book::Book():
	ISBN("0"),
	title("title"),
	author("author"),
	category("category"),
	index("Index0"),
	count(1),
	favor(0)
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
		out << "Index: " << index << endl;
		out << "Count: " << count << endl;
		out << "Favor: " << favor << endl;
	}
	else { //Write to File
		out << endl << ISBN << endl;
		out << title << endl;
		out << author << endl;
		out << category << endl;
		out << index << endl;
		out << count << endl;
		out << favor << endl;
		out << "----------------";
	}
	return out;
}

//Reads in a single book from a stream and adds it to the book database
istream& Book::operator>>(istream& in) {
	string line;
	if(!in.eof())
		for (int i = 0; i < 8; i++) {
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
					index = line;
					break;
				case 5:
					count = stoi(line);
					break;
				case 6:
					favor = stoi(line);
					break;
				case 7: //line delimiter
					break;
			}
		}
	return in;
}