//Instantiation of Book Object

class Book {
private:
	long ISBN;
	string title;
	string author;
	string category;
	int id; //Book ID
	string reader; //Borrower
	long start; //start date
	long end; //expiration date
public:
	//Accessors
	long getISBN();
	string getTitle();
	string getAuthor();
	string getCategory();
	int getID();
	string getBorrower();
	long getStartDate();
	long getExpirationDate();
};

/* ====Book Database Format==== 
isbn
title
author
category
id
borrowerName
start
end
-------------
...
*/