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
ostream& operator<<(ostream& out, Book& b){
	if (&out == &cout) { //Console Display
		out << "ISBN: " << b.ISBN << endl;
		out << "Title: " << b.title << endl;
		out << "Author: " << b.author << endl;
		out << "Category: " << b.category << endl;
		out << "Index: " << b.index << endl;
		out << "Count: " << b.count << endl;
		out << "Favor: " << b.favor << endl;
	}
	else { //Write to File
		out << endl << b.ISBN << endl;
		out << b.title << endl;
		out << b.author << endl;
		out << b.category << endl;
		out << b.index << endl;
		out << b.count << endl;
		out << b.favor << endl;
		out << "----------------";
	}
	return out;
}

//Reads in a single book from a stream and adds it to the book database
istream& operator>>(istream& in, Book& b) {
	string line;
	if(!in.eof())
		for (int i = 0; i < 8; i++) {
			getline(in>>ws, line);
			if (line.empty())
				break;
			switch (i) {
				case 0:
					b.ISBN = line;
					break;
				case 1:
					b.title = line;
					break;
				case 2:
					b.author = line;
					break;
				case 3:
					b.category = line;
					break;
				case 4:
					b.index = line;
					break;
				case 5:
					b.count = stoi(line);
					break;
				case 6:
					b.favor = stoi(line);
					break;
				case 7: //line delimiter
					break;
			}
		}
	return in;
}