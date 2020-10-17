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
	void output();

	long getISBN();
	string getTitle();
	string getAuthor();
	string getCategory();
	int getID();
	string getBorrower();
	long getStartDate();
	long getExpirationDate();

	void SetIsbn(long ISBN);
	void SetTitle(string title);
	void SetAuthor(string author);
	void SetCategory(string category);
	void Setid(int id);
	void SetBorrower(string reader);
	void SetStartDate(long start);
	void SetExpirationDate(long end);
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