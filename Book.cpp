// Xiangfeng Lin for the cpp file 10/16

#include <iostream>
#include <iomanip>
#include "Book.h"
#include <string>

using namespace std;

Book::Book() {}

void Book::output()  //show the information of the book
{
	cout << "\tISBN:" << ISBN << endl;
	cout << "\ttitle:" << title << endl;
	cout << "\tauthor:" << author << endl;
	cout << "\tcategory:" << category << endl;
	cout << "\tID:"<< id << endl;
	cout << "\tReader:" << reader << endl;
	cout << "\tStart date:" << start << endl;
	cout << "\tExpiration date:" << end << endl;
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
