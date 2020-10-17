// Xiangfeng Lin for the cpp file

#include <iostream>
#include <iomanip>
#include "Book.h"
#include <string>

using namespace std;

Book::Book() {}

void Book::output()  //show the information of the book
{
	cout << "              ISBN:" << ISBN << endl;
	cout << "              title:" << title << endl;
	cout << "              author:" << author << endl;
	cout << "              category:" << category << endl;
	cout << "			   ID:"<< id << endl;
	cout << "			   Reader:" << reader << endl;
	cout << "              Start date:" << start << endl;
	cout << "              Expiration date:" << end << endl;
}

long Book::ISBN()
{
	return ISBN;
}

string Book::getTitle()
{
	return title;
}

string Book::getAuthor()
{
	return author;
}

string Book::getCategory()
{
	return category;
}

int Book::getID()
{
	return id;
}

string Book::getBorrower()
{
	return reader;
}

long Book::getStartDate()
{
	return start;
}

long Book::getExpirationDate()
{
	return end;
}


void Book::SetIsbn(long ISBN)
{
	this->ISBN = ISBN;
}

void Book::SetTitle(string title)
{
	this->title = title;
}

void Book::SetAuthor(string author)
{
	this->author = author;
}

void SetCategory(string category)
{
	this->category = category;
}

void Setid(int id)
{
	this->id = id;
}

void SetBorrower(string reader)
{
	this->reader = reader;
}

void SetStartDate(long start)
{
	this->start = start;
}

void SetExpirationDate(long end)
{
	this->end = end;
}
