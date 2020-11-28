#include <string>
#include "Book.h"
#include "Reader.h"
using namespace std;

class Copy : public Book {
private:
	int id;
	Book book;
	string borrower; //Current Borrower - SAVED AS USERNAME
	string reserver; //Current Reserver - SAVED AS USERNAME
	bool available;
	long start; //start date
	long end; //expiration date
public:
	//Default Constructor
	Copy();
	Copy(int id, Book book, string borrower, string reserver, bool available, long start, long end);
	
	//Accessors
	int getID();
	Book getBook();
	string getBorrower(); 
	string getReserver();
	bool getAvailability();
	long getStartDate();
	long getExpirationDate();

	//Mutators
	void setID(int id);
	void setBorrower(string borrower);
	void setReserver(string reserver);
	void setAvailability(bool available);
	void setStartDate(long start);
	void setExpirationDate(long end);
};